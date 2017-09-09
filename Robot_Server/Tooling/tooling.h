#ifndef TOOLING_H
#define TOOLING_H
#include <QObject>
#include <QTcpSocket>
#include <QLabel>
#include <QTableWidget>
#include <QMessageBox>
#include <task.h>
#include <base.h>
#include <Event/EventManager.h>
#include <Event/eventmessage.h>
#include <Tooling/tooling_communication.h>
#include <command.h>

using namespace Mage;

class Tooling : public QObject
{
    Q_OBJECT

public:

    enum State {ONLINE, OFFLINE, START_TESTING}; //紀錄目前機台的狀態, 給GUI用

    Tooling(int _toolingNum);

    ~Tooling();

    int offsetNum; //所對應的Base座標系 是哪個Base

    int toolingNum; //第幾號機箱

    void setSocket(QTcpSocket *tcpSocket);

    void timeoutFailFire();

    //紀錄目前機台的狀態, 給GUI用
    void updateState(Tooling::State _state)
    {
        state = _state;
        emit updateGUI(state);
    }

signals:

    void updateGUI(Tooling::State);

private:

    Tooling_Communication *communication;

    QTcpSocket *socket;

    Command command;

    QMessageBox msgBox;

    //紀錄目前機台的狀態, 給GUI用
    State state;

    void fireEvent(const QString& str, const EventMessage& msg) {
      // Fire the event and all the subscribed class methods will get called.
      EventManager *myEventManager = EventManager::Instance();
      myEventManager->execute(str, msg);
    }

    //監聽收到NoACK類型封包的事件
    void No_ACK_Event_Listener(const EventMessage& msg);

    void Tooling_Idle_Fire(const EventMessage& msg);

    void powerOn_Listener(const EventMessage& msg);

    void powerOff_Listener(const EventMessage& msg);

    void sendSocket_Listener(const EventMessage& msg);    

private slots:

    //更新connection 的狀態
    void updateConnectionState(Tooling_Communication::State);
};

#endif // TOOLING_H