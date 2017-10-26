#ifndef TASKMANAGER_H
#define TASKMANAGER_H
#include "event/eventmessage.h"
#include "event/EventManager.h"
#include "command.h"
#include "QFile"

using namespace Mage;

class TaskManager
{
public:
    TaskManager();

    ~TaskManager();

    static bool comboMode;

    //監聽事件:收到ACK回復時觸發
    void ACK_Listener(const EventMessage& msg);
    //監聽事件:收到所有種類DONE回復時觸發
    void DONE_Listener(const EventMessage& msg);
    //監聽事件:收到ERROR訊息時觸發
    void ERROR_Listener(const EventMessage& msg);

    //監聽事件:Tooling事件
    void Tooling_TestPass_Listener(const EventMessage& msg);
    void Tooling_TestFail_Listener(const EventMessage& msg);
    void Tooling_Boot_Listener(const EventMessage& msg);
    void Tooling_TimeoutFail_Listener(const EventMessage& msg);
    void Tooling_Idle_Listener(const EventMessage& msg);
    void Tooling_ReTest_Listener(const EventMessage& msg);

    //監聽事件: CCD事件
    void CCD_ScanError_Listener(const EventMessage& msg);

    //監聽事件:Robot事件
    void Robot_UpdateBase_Listener(const EventMessage &msg);
    //監聽事件:三個List的變化
    void Task_workList_DONE_Add(const EventMessage& msg);

private:

    Command command;

    QFile *logFile;

    //將DoneList裡的資料記錄到Log
    void recordLog();
    //將DoneList裡的資料到達一定量時做清除
    void clearDoneList();

    void fireEvent(const QString& str, const EventMessage& msg) {
      // Fire the event and all the subscribed class methods will get called.
      EventManager *myEventManager = EventManager::Instance();
      myEventManager->execute(str, msg);
    }

};

#endif // TASKMANAGER_H
