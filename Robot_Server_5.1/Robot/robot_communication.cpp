#include "robot_communication.h"

Robot_Communication::Robot_Communication(const QString& _IP, const int& _port)
{
    socket = new QTcpSocket;
    timer = new QTimer;
    timer->setInterval(5000);
    IP = _IP;
    port = _port;

    msgBox.setStandardButtons(QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.setWindowTitle("Warning");
    msgBox.setIcon(QMessageBox::Warning);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(timer, SIGNAL(timeout()), this, SLOT(reSendSocket()));
}

Robot_Communication::~Robot_Communication()
{
    delete socket;
    delete timer;
}

void Robot_Communication::connectToHost()
{
    socket->connectToHost(IP, port);

    if (socket->waitForConnected(1000))
    {
        updateState(Robot_Communication::ONLINE);
        qDebug("Connected to Host!");
    }else
    {
        updateState(Robot_Communication::OFFLINE);
        msgBox.setText("Robot connect Error!");
        msgBox.exec();
        qDebug("Robot connected error!");
    }
}

void Robot_Communication::readyRead()
{
    QString str = socket->readAll();

    QString ID = str.split(",").at(0);

    //比對ID是否正確
    if(!IDList.contains(ID))
    {
        qDebug() << "Robot Comunication Exception:" + str;
        return;
    }

    EventMessage msg(ID, EventMessage::ACK, EventMessage::FromRobot);

    if(str.contains("ACK"))
    {
        if(ACK_ID == ID)
        {
            updateState(Robot_Communication::RECEIVE_ACK);
            qDebug() << "ACK Back << " + str;
            ACK_ID.clear();
            fireEvent(command.robot_communication_event.ACK, msg);
        }
    }else if(str.contains("DONE"))
    {
        updateState(Robot_Communication::RECEIVE_DONE);
        qDebug() << "DONE Back << " + str;
        IDList.removeOne(ID);
        fireEvent(command.robot_communication_event.DONE, msg);
    }
}

void Robot_Communication::sendSocketToRobot_CMD(QString ID, QString from, QString to)
{
    QString str = "<ROBOT><CMD ID=\"" + ID + "\" FROM=\"" + from + "\" TO=\"" + to + "\">1</CMD></ROBOT>";

    //將ID記錄到各暫存列表
    IDList.append(ID);
    ACK_ID = ID;
    reSendText = str;

    //發送資料
    socket->write(str.toLatin1());
    qDebug() << "SendToRobot: " + str;

    //開始定時重送封包
    timer->start();
}

void Robot_Communication::sendSocketToRobot_UpdateBase(QString ID, QString N, const QString &X, const QString &Y,
                                                       const QString &Z, const QString &A, const QString &B, const QString &C)
{
    QString str = "<ROBOT><UPDATEBASE ID=\"" + ID + "\" X=\"" + X + "\" Y=\"" + Y + "\" Z=\"" + Z
            +"\" A=\"" + A +"\" B=\"" + B +"\" C=\"" + C +"\">" + N + "</UPDATEBASE></ROBOT>";

    //將ID記錄到各暫存列表
    IDList.append(ID);
    ACK_ID = ID;
    reSendText = str;

    //發送資料
    socket->write(str.toLatin1());
    qDebug() << "SendToRobot: " + str;

    //開始定時重送封包
    timer->start();
}

void Robot_Communication::sendSocketToRobot_CMDtoTooling(QString ID, QString from, QString to, QString reLoad)
{
    QString str = "<ROBOT><CMD ID=\"" + ID + "\" FROM=\"" + from + "\" TO=\"" + to + "\" RELOAD=\"" + reLoad + "\">1</CMD></ROBOT>";

    //將ID記錄到各暫存列表
    IDList.append(ID);
    ACK_ID = ID;
    reSendText = str;

    //發送資料
    socket->write(str.toLatin1());
    qDebug() << "SendToRobot: " + str;

    //開始定時重送封包
    timer->start();
}

void Robot_Communication::sendSocketToRobot_Machine(QString ID, QString power, QString N)
{
    QString str = "<ROBOT><MACHINE ID=\"" + ID + "\" POWER=\"" + power + "\">" + N + "</MACHINE></ROBOT>";

    //將ID記錄到各暫存列表
    IDList.append(ID);
    ACK_ID = ID;
    reSendText = str;

    //發送資料
    socket->write(str.toLatin1());
    qDebug() << "SendToRobot: " + str;

    //開始定時重送封包
    timer->start();
}

void Robot_Communication::sendSocketToRobot_UpdateTray(QString ID)
{
    QString str = "<ROBOT><CMD ID=\"" + ID + "\" FROM=\"0\">1</CMD></ROBOT>";

    //將ID記錄到各暫存列表
    IDList.append(ID);
    ACK_ID = ID;
    reSendText = str;

    //發送資料
    socket->write(str.toLatin1());
    qDebug() << "SendToRobot: " + str;

    //開始定時重送封包
    timer->start();
}

void Robot_Communication::reSendSocket()
{
    if(ACK_ID.isEmpty())
    {
        timer->stop();
        return;
    }
    socket->write(reSendText.toLatin1());
    qDebug() << "Re SendToRobot: " + reSendText + "......";
}

void Robot_Communication::disconnected()
{
    qDebug() << "Robot disconnected.";
    updateState(Robot_Communication::OFFLINE);
}
