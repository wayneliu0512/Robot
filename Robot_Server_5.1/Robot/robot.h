#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QMessageBox>
#include <task.h>
#include <base.h>
#include <robot/robot_communication.h>
#include <event/eventmessage.h>
#include <command.h>
#include <event/EventManager.h>


using namespace Mage;

class Robot: public QObject
{
    Q_OBJECT
public:

    enum State{ ONLINE, OFFLINE, IN_ACTION};

    Robot(QString _IP, int _port);

    ~Robot();

    static bool ActionIdle;

    static bool NonActionIdle;

    void connectToRobot();

    void setBase(const QVector<Base>& _baseList);

    //紀錄目前機台的狀態, 給GUI用
    void updateState(Robot::State _state)
    {
        state = _state;
        emit updateGUI(state);
    }

signals:

    void updateGUI(Robot::State);

private:

    Robot_Communication *communication;

    QList<Task> robotRunningList;

    QString IP;
    int port;
    QTcpSocket *socket;
    Command command;
    State state;

    QMessageBox msgBox;
    //監聽收到DONE封包事件
    void DONE_Event_Listener(const EventMessage& msg);
    //監聽執行動作型任務
    void Excute_ActionTask(const EventMessage& msg);
    //監聽執行非動作型任務
    void Excute_NonActionTask(const EventMessage& msg);

    //儲存Base座標系的列表
    QVector<Base> baseList;

    void fireEvent(const QString& str, const EventMessage& msg) {
      // Fire the event and all the subscribed class methods will get called.
      EventManager *myEventManager = EventManager::Instance();
      myEventManager->execute(str, msg);
    }
private slots:

    //更新connection 的狀態
    void updateConnectionState(Robot_Communication::State _state);

};

#endif // ROBOT_H
