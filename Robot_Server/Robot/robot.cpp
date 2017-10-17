#include "robot.h"
#include <QThread>
bool Robot::ActionIdle = true;
bool Robot::NonActionIdle = true;

Robot::Robot(QString _IP, int _port)
{
//    socket = new QTcpSocket;

    //訂閱 收到DONE回復時觸發 事件
    EventManager *myEventManager = EventManager::Instance();
    myEventManager->subscribe(command.robot_communication_event.DONE, this, &Robot::DONE_Event_Listener);
    myEventManager->subscribe(command.robot_event.ActionTask, this, &Robot::Excute_ActionTask);
    myEventManager->subscribe(command.robot_event.NonActionTask, this, &Robot::Excute_NonActionTask);

    IP = _IP;
    port = _port;

    msgBox.setStandardButtons(QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle("Warning");

    communication = new Robot_Communication(IP, port);

    connect(communication, SIGNAL(update(Robot_Communication::State)),
            this, SLOT(updateConnectionState(Robot_Communication::State)));
}

Robot::~Robot()
{
    delete communication;
}

void Robot::connectToRobot()
{
    if(!communication)
    {
        communication = new Robot_Communication(IP, port);

        connect(communication, SIGNAL(update(Robot_Communication::State)),
                this, SLOT(updateConnectionState(Robot_Communication::State)));
    }
    communication->connectToHost();
}

void Robot::Excute_ActionTask(const EventMessage &msg)
{
    Task task = *msg.task;
    robotRunningList.append(task);

    //機台號碼
    QString num = QString::number(task.targetID);

    //讓Robot通訊層去傳送各種指令
    if(task.command == command.robot_command.toScanSN)
    {
        communication->sendSocketToRobot_CMD(task.ID, "10", num);
    }else if(task.command == command.robot_command.toScanMAC)
    {
        communication->sendSocketToRobot_CMD(task.ID, "13", "13");
    }else if(task.command == command.robot_command.toScanFAIL)
    {
        communication->sendSocketToRobot_CMD(task.ID, "13", "12");
    }else if(task.command == command.robot_command.toTooling)
    {
        communication->sendSocketToRobot_CMD(task.ID, "13", num);
    }else if(task.command == command.robot_command.toPASS)
    {
        communication->sendSocketToRobot_CMDtoTooling(task.ID, num, "11", "0");
    }else if(task.command == command.robot_command.toFAIL)
    {
        communication->sendSocketToRobot_CMDtoTooling(task.ID, num, "12", "0");
    }else if(task.command == command.robot_command.toReTest)
    {
        communication->sendSocketToRobot_CMDtoTooling(task.ID, num, num, num);
    }else if(task.command == command.tooling_command.powerOn)
    {
        communication->sendSocketToRobot_Machine(task.ID, "1", num);
    }else if(task.command == command.tooling_command.powerOff)
    {
        communication->sendSocketToRobot_Machine(task.ID, "0", num);
    }else if(task.command == command.robot_command.updateBase1 || task.command == command.robot_command.updateBase2
             ||task.command == command.robot_command.updateBase3)
    {
        Base base = baseList.at(num.toInt() - 1);
        communication->sendSocketToRobot_UpdateBase(task.ID, num, base.X, base.Y, base.Z, base.A, base.B, base.C);
    }else if(task.command == command.robot_command.updateTray)
    {
        communication->sendSocketToRobot_UpdateTray(task.ID);
    }
   //傳socket給Robot
   //QThread::sleep(1);
}

void Robot::Excute_NonActionTask(const EventMessage &msg)
{
    Task task = *msg.task;
    robotRunningList.append(task);

    //機台號碼
    QString num = QString::number(task.targetID);

    //讓Robot通訊層去傳送各種指令
    if(task.command == command.tooling_command.powerOn)
    {
        communication->sendSocketToRobot_Machine(task.ID, "1", num);
    }else if(task.command == command.tooling_command.powerOff)
    {
        communication->sendSocketToRobot_Machine(task.ID, "0", num);
    }
    //QThread::sleep(1);
}

void Robot::DONE_Event_Listener(const EventMessage& msg)
{
    //尋找Robot執行中列表裡是否有此ID
    for(int i = 0; i < robotRunningList.length(); i++)
    {
        if(msg.ID == robotRunningList.at(i).ID)
        {
            robotRunningList.removeAt(i);
        }
    }

}

void Robot::setBase(const QVector<Base> &_baseList)
{
    baseList = _baseList;
}

void Robot::updateConnectionState(Robot_Communication::State _state)
{
    switch(_state)
    {

    case Robot_Communication::ONLINE:
    case Robot_Communication::RECEIVE_DONE:
        updateState(Robot::ONLINE);
        break;

    case Robot_Communication::OFFLINE:
        updateState(Robot::OFFLINE);
        break;

    case Robot_Communication::RECEIVE_ACK:
        updateState(Robot::IN_ACTION);
        break;

    }
}
