#ifndef TOOLING_COMMUNICATION_H
#define TOOLING_COMMUNICATION_H

#include <QTcpSocket>
#include <QDebug>
#include <QObject>
#include <event/EventManager.h>
#include <event/eventmessage.h>
#include <command.h>
#include <QLabel>


using namespace Mage;

class Tooling_Communication : public QObject
{
    Q_OBJECT
public:

    enum State{ONLINE, OFFLINE, RECEIVE_NOACK};

    Tooling_Communication(int _toolingNum);

    ~Tooling_Communication();

    void setSocket(QTcpSocket *_socket);

    void sendData(QString str);

    //更新連線狀態
    void updateState(State _state)
    {
        state = _state;
        emit update(state);
    }

signals:

    void update(Tooling_Communication::State);

private:

    QTcpSocket *socket;

    int toolingNum;

    Command command;

    State state;

    void fireEvent(const QString& str, const EventMessage& msg) {
      // Fire the event and all the subscribed class methods will get called.
      EventManager *myEventManager = EventManager::Instance();
      myEventManager->execute(str, msg);
    }

private slots:

    void readyRead();

    void disconnected();
};

#endif // TOOLING_COMMUNICATION_H
