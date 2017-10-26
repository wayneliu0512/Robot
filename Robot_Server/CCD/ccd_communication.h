#ifndef CCD_COMMUNICATION_H
#define CCD_COMMUNICATION_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <Event/EventManager.h>
#include <Event/eventmessage.h>

using namespace Mage;

class CCD_Communication : public QObject
{
    Q_OBJECT
public:

    enum State { ONLINE, OFFLINE, RECEIVE_ACK, RECEIVE_DONE};

    CCD_Communication(QTcpSocket *_socket);

    ~CCD_Communication();

    void sendSocketToCCD(const QString &_ID, const QString &_CMD, int _toolingNum);

signals:

    void update(CCD_Communication::State);

private:

    QTcpSocket *socket;

    //暫存 等待ACK回傳的 ID, 暫存等待DONE回傳的 ID
    QString ACK_ID, DONE_ID;
    
    //暫存要重傳的資料
    QByteArray reSendText;

    //Timer for ACK reSend every 5 senconds
    QTimer *timer;

    Command command;

    State state;

    int toolingNum;

    void updateSN(const QString &_SN);

    void updateMAC(const QString &_MAC);

    void fireEvent(const QString& str, const EventMessage& msg) {
      // Fire the event and all the subscribed class methods will get called.
      EventManager *myEventManager = EventManager::Instance();
      myEventManager->execute(str, msg);
    }

    //更新連線狀態
    void updateState(State _state)
    {
        state = _state;
        emit update(state);
    }

private slots:

    void readyRead();

    void disconnected();

    void ACK_timeout();
};

#endif // CCD_COMMUNICATION_H
