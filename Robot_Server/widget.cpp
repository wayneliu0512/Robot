#include "widget.h"
#include "ui_widget.h"
#include <QInputDialog>
#include <QDialogButtonBox>
#include <snprescandialog.h>

QList<Task> Widget::workList_Waiting;
QList<Task> Widget::workList_InAction;
QList<Task> Widget::workList_Done;
int Widget::flashCounter = 0;

bool Widget::systemOn = false;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{   
    ui->setupUi(this);
//    this->setFixedSize(671, 599);

    setting = new StartUpSetting;
    createAllEvent();

    flashTimer = new QTimer;
    server = new QTcpServer;
    socket = new QTcpSocket;

    tooling_1 = new Tooling(1);
    tooling_1->setLogPath(setting->toolingLogPath);
    tooling_GUI_1 = new Tooling_GUI(tooling_1, ui->listWidget_Box1, ui->pixmap_Box1, ui->lcdNumber_Box1, flashTimer);

    tooling_2 = new Tooling(2);
    tooling_2->setLogPath(setting->toolingLogPath);
    tooling_GUI_2 = new Tooling_GUI(tooling_2, ui->listWidget_Box2, ui->pixmap_Box2, ui->lcdNumber_Box2, flashTimer);

    tooling_3 = new Tooling(3);
    tooling_3->setLogPath(setting->toolingLogPath);
    tooling_GUI_3 = new Tooling_GUI(tooling_3, ui->listWidget_Box3, ui->pixmap_Box3, ui->lcdNumber_Box3, flashTimer);

    ccd = new CCD;
    ccd_GUI = new CCD_GUI(ccd, ui->pixmap_Barcode, ui->label_SN, ui->label_MAC);

    robot = new Robot(setting->robotIP, setting->robotPort);
    robot_GUI = new Robot_GUI(robot, ui->label_RobotTarget, ui->pixmap_Robot, flashTimer);
    robot->connectToRobot();
//    robot->setBase(setting->offsetList);

    taskManager = new TaskManager;
    actionManager = new ActionManager;

    msgBox.setStandardButtons(QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.setWindowTitle("Warning");
    msgBox.setIcon(QMessageBox::Warning);

    connect(flashTimer, SIGNAL(timeout()), this, SLOT(flashingTimerReset()));
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    flashTimer->setInterval(500);
    flashTimer->start();
    serverOn(setting->port);

}

Widget::~Widget()
{
    delete setting;
    delete tooling_1;
    delete tooling_GUI_1;
    delete tooling_2;
    delete tooling_GUI_2;
    delete tooling_3;
    delete tooling_GUI_3;
    delete ccd;
    delete ccd_GUI;
    delete robot;
    delete robot_GUI;
    delete taskManager;
    delete actionManager;
    workList_Done.clear();
    workList_InAction.clear();
    workList_Waiting.clear();
}

void Widget::createAllEvent()
{
    EventManager *myEventManager = EventManager::Instance();

    //Create Robot Event
    myEventManager->createEvent(command.robot_communication_event.ACK);
    myEventManager->createEvent(command.robot_communication_event.DONE);
    myEventManager->createEvent(command.robot_event.Busy);
    myEventManager->createEvent(command.robot_event.ActionTask);
    myEventManager->createEvent(command.robot_event.NonActionTask);
    myEventManager->createEvent(command.robot_event.updateBase);

    //Create Tooling Event
    myEventManager->createEvent(command.tooling_communication_event.NoACK);
    myEventManager->createEvent(command.tooling_event.testPASS);
    myEventManager->createEvent(command.tooling_event.testFAIL);
    myEventManager->createEvent(command.tooling_event.timeoutFail);
    myEventManager->createEvent(command.tooling_event.boot);
    myEventManager->createEvent(command.tooling_event.takeOut);
    myEventManager->createEvent(command.tooling_event.Idle);
    myEventManager->createEvent(command.tooling_event.powerOn);
    myEventManager->createEvent(command.tooling_event.powerOff);
    myEventManager->createEvent(command.tooling_event.sendSocket);

    //Create CCD Event
    myEventManager->createEvent(command.ccd_event.startScanSN);
    myEventManager->createEvent(command.ccd_event.startScanMAC);
    myEventManager->createEvent(command.ccd_event.scanError);
    myEventManager->createEvent(command.ccd_communication_event.ACK);
    myEventManager->createEvent(command.ccd_communication_event.DONE);

    //Create Task Event
    myEventManager->createEvent(command.task_event.workList_Waiting_Add);
    myEventManager->createEvent(command.task_event.workList_Waiting_Removed);
    myEventManager->createEvent(command.task_event.workList_InAction_Add);
    myEventManager->createEvent(command.task_event.workList_InAction_Removed);
    myEventManager->createEvent(command.task_event.workList_DONE_Add);
    myEventManager->createEvent(command.task_event.workList_DONE_Removed);
    myEventManager->createEvent(command.task_event.Error);

    //Subscribe Task Event
    myEventManager->subscribe(command.task_event.workList_DONE_Add, this, &Widget::updateTable);
    myEventManager->subscribe(command.task_event.workList_DONE_Removed, this, &Widget::updateTable);
    myEventManager->subscribe(command.task_event.workList_InAction_Add, this, &Widget::updateTable);
    myEventManager->subscribe(command.task_event.workList_InAction_Removed, this, &Widget::updateTable);
    myEventManager->subscribe(command.task_event.workList_Waiting_Add, this, &Widget::updateTable);
    myEventManager->subscribe(command.task_event.workList_Waiting_Removed, this, &Widget::updateTable);
}

void Widget::serverOn(int _port)
{
    if(!server->listen(QHostAddress::Any, _port))
    {
        msgBox.setText("Server could not start!");
        msgBox.show();
    }
    else
    {
        qDebug() << "Server Start!";
    }
}

void Widget::newConnection()
{
    QTcpSocket* _socket = new QTcpSocket;
    _socket = server->nextPendingConnection();
    qDebug() << "New connection : " + _socket->peerAddress().toString();
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void Widget::readyRead()
{

    QTcpSocket * _socket = qobject_cast<QTcpSocket*>(sender());

    QString stringFromClient;

    stringFromClient = _socket->readAll();

    if(stringFromClient == "tooling1")
    {
        tooling_1->setSocket(_socket);
    }
    else if(stringFromClient == "tooling2")
    {
        tooling_2->setSocket(_socket);
    }
    else if(stringFromClient == "tooling3")
    {
        tooling_3->setSocket(_socket);
    }
    else if(stringFromClient == "ccd")
    {
        ccd->setSocket(_socket);
    }

    disconnect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

//Update workList_Waiting
void Widget::changeTable1()
{
    ui->tableWidget_1->setRowCount(0);
    if(workList_Waiting.empty())
    {
        return;
    }
    foreach(Task task, Widget::workList_Waiting)
    {
        QTableWidgetItem *CommandItem = new QTableWidgetItem(task.command);
        QTableWidgetItem *TargetItem = new QTableWidgetItem(task.targetToString());
        QTableWidgetItem *TargetIDItem = new QTableWidgetItem(QString::number(task.targetID));
        int row = ui->tableWidget_1->rowCount();
        ui->tableWidget_1->insertRow(row);
        ui->tableWidget_1->setItem(row, 0, TargetItem);
        ui->tableWidget_1->setItem(row, 1, TargetIDItem);
        ui->tableWidget_1->setItem(row, 2, CommandItem);
    }
}

//Update workList_InAction
void Widget::changeTable2()
{
    ui->tableWidget_2->setRowCount(0);
    if(workList_InAction.empty())
    {
        return;
    }
    foreach(Task task, Widget::workList_InAction)
    {
        QTableWidgetItem *CommandItem = new QTableWidgetItem(task.command);
        QTableWidgetItem *TargetItem = new QTableWidgetItem(task.targetToString());
        QTableWidgetItem *TargetIDItem = new QTableWidgetItem(QString::number(task.targetID));
        int row = ui->tableWidget_2->rowCount();
        ui->tableWidget_2->insertRow(row);
        ui->tableWidget_2->setItem(row, 0, TargetItem);
        ui->tableWidget_2->setItem(row, 1, TargetIDItem);
        ui->tableWidget_2->setItem(row, 2, CommandItem);
    }
}

//Update workList_Done
void Widget::changeTable3()
{
    ui->tableWidget_3->setRowCount(0);
    if(workList_Done.empty())
    {
        return;
    }
    foreach(Task task, Widget::workList_Done)
    {
        QTableWidgetItem *CommandItem = new QTableWidgetItem(task.command);
        QTableWidgetItem *TargetItem = new QTableWidgetItem(task.targetToString());
        QTableWidgetItem *TargetIDItem = new QTableWidgetItem(QString::number(task.targetID));
        int row = ui->tableWidget_3->rowCount();
        ui->tableWidget_3->insertRow(row);
        ui->tableWidget_3->setItem(row, 0, TargetItem);
        ui->tableWidget_3->setItem(row, 1, TargetIDItem);
        ui->tableWidget_3->setItem(row, 2, CommandItem);
    }
}

void Widget::on_Button_Start_clicked()
{
    if(systemOn)
        return;

    if(!checkDeviceAllConnected())
        return;

    preScanBarcode();

    //警告人員淨空, 手臂將開始運行
    msgBox.setText("Please make sure keep personnel clearance and free of obstacle!\nRobot is about to operate!");
    msgBox.exec();

    //觸發updateBase 任務派發
    EventMessage msg;
    fireEvent(command.robot_event.updateBase, msg);

    //開始運行
    actionManager->start();
}

bool Widget::checkDeviceAllConnected()
{
    //檢查手臂連線狀態
    while(robot->state != Robot::ONLINE)
    {
        if(QMessageBox::critical(this, tr("Error"), tr("Robot connection error\nDo you want to reconnect?"),
                                 QMessageBox::Ok,QMessageBox::Cancel) == QMessageBox::Ok)
        {
            robot->connectToRobot();
        }else{
            return false;
        }
    }

    //檢查CCD連線狀態
    if(ccd->state == CCD::OFFLINE)
    {
        QMessageBox::critical(this, tr("Error"), tr("CCD connection error"),QMessageBox::Ok);
        return false;
    }

    //檢查tooling連線狀態, 至少要有一台連線
    if(tooling_1->state == Tooling::OFFLINE && tooling_2->state == Tooling::OFFLINE && tooling_3->state == Tooling::OFFLINE )
    {
        QMessageBox::critical(this, tr("Error"), tr("Tooling connection error"),QMessageBox::Ok);
        return false;
    }

    return true;
}

void Widget::preScanBarcode()
{
    //開啟 Scan Barcode 的 視窗
    SNpreScanDialog *scanDialog = new SNpreScanDialog(setting);
    scanDialog->exec();

    //更新新的offsetList給手臂
    robot->setBase(scanDialog->newOffsetList);

    delete scanDialog;
}

void Widget::on_Button_Stop_clicked()
{
    actionManager->stop();
}

void Widget::updateTable(const EventMessage& msg)
{
    changeTable1();
    changeTable2();
    changeTable3();
}

//閃爍用的timer
void Widget::flashingTimerReset()
{
    if(flashCounter == 100)
        flashCounter = 0;
    flashCounter++;
}
