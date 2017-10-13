#ifndef CCD_H
#define CCD_H
#include <QObject>
#include "Event/EventManager.h"
#include "Event/eventmessage.h"
#include "ccd_communication.h"

class QString;
class QTcpSocket;
class Command;

using namespace Mage;

class CCD : public QObject
{
    Q_OBJECT
public:

    enum State { ONLINE, OFFLINE, TAKING_SHOT, FINISH_SHOT};

    CCD();

    ~CCD();

    void setSocket(QTcpSocket *_socket);

    static QString SN, MAC;

    //紀錄目前機台的狀態, 給GUI用
    void updateState(CCD::State _state)
    {
        state = _state;
        emit updateGUI(state);
    }

    State state;

signals:

    void updateGUI(CCD::State);

private:

    CCD_Communication *communication;

    Command command;
    //暫時的假ID, 製造假的ACK回傳
    QString ID;

    int toolingNum;

    void fireEvent(const QString& str, const EventMessage& msg) {
      // Fire the event and all the subscribed class methods will get called.
      EventManager *myEventManager = EventManager::Instance();
      myEventManager->execute(str, msg);
    }

    void startScanSN_Listener(const EventMessage& msg);
    void startScanMAC_Listener(const EventMessage& msg);

private slots:

    void updateConnectionState(CCD_Communication::State _state);

};

#endif // CCD_H
