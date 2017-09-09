#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include <QObject>
#include <QTimer>
#include <Event/EventManager.h>
#include <Event/eventmessage.h>
#include <command.h>

using namespace Mage;

class ActionManager : public QObject
{
    Q_OBJECT
public:
    ActionManager();

    ~ActionManager();

    void start();

    void stop();

private:
    //多少時間執行一次ActionManage
    QTimer *timer;

    Command command;

    void dispatch_First_Task();

    void dispatch_First_Action_Task();

    void dispatch_First_NonAction_Task();

    void fireEvent(const QString& str, const EventMessage& msg) {
      // Fire the event and all the subscribed class methods will get called.
      EventManager *myEventManager = EventManager::Instance();
      myEventManager->execute(str, msg);
    }

private slots:

    void ActionManage();
};

#endif // ACTIONMANAGER_H
