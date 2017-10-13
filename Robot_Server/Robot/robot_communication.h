#ifndef ROBOT_COMMUNICATION_H
#define ROBOT_COMMUNICATION_H

#include <QTcpSocket>
#include <QDebug>
#include <QObject>
#include <Event/EventManager.h>
#include <Event/eventmessage.h>
#include <command.h>
#include <QTimer>
#include "QMessageBox"

using namespace Mage;

class Robot_Communication : public QObject
{
    Q_OBJECT
public:

    enum State{ONLINE, OFFLINE, RECEIVE_DONE, RECEIVE_ACK, RECEIVE_ERROR};

    Robot_Communication(const QString& _IP, const int& _port);

    ~Robot_Communication();

    void connectToHost();//連結到Server

    //手臂動作傳輸格式
    void sendSocketToRobot_CMD(QString ID, QString from, QString to);

    //手臂UpdateBase格式
    void sendSocketToRobot_UpdateBase(QString ID, QString N, const QString &X, const QString &Y, const QString &Z
                                      , const QString &A, const QString &B, const QString &C);

    //手臂動作格式 (有重送指令)
    void sendSocketToRobot_CMDtoTooling(QString ID, QString from, QString to, QString reLoad);

    //透過手臂控制機台Power格式
    void sendSocketToRobot_Machine(QString ID, QString power, QString N);

    //透過手臂控制LightTower燈號
    void sendSocketToRobot_LightColor(QString ID, QString color);

    void sendSocketToRobot_UpdateTray(QString ID);

    //更新連線狀態
    void updateState(State _state)
    {
        state = _state;
        emit update(state);
    }

signals:

    void update(Robot_Communication::State);

private:

    //比對ID是否正確用的
    QList<QString> IDList;

    //比對ACK_ID用的(重傳用)
    QString ACK_ID;

    //重傳用暫存
    QString reSendText;

    QTcpSocket *socket;

    Command command;

    //定時重新發送ACK用的
    QTimer *timer;

    QMessageBox msgBox;

    QString IP;
    int port;

    State state;

    void fireEvent(const QString& str, const EventMessage& msg) {
      // Fire the event and all the subscribed class methods will get called.
      EventManager *myEventManager = EventManager::Instance();
      myEventManager->execute(str, msg);
    }

private slots:

    void readyRead();

    void disconnected();

    void reSendSocket();

};

#endif // ROBOT_COMMUNICATION_H
