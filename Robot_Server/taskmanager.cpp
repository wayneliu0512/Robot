#include "widget.h"
#include "taskmanager.h"

bool TaskManager::comboMode = false;

TaskManager::TaskManager()
{
    logFile = new QFile("Robot_log.log");
    logFile->open(QIODevice::WriteOnly | QIODevice::Text);

    EventManager *myEventManager = EventManager::Instance();
    myEventManager->subscribe(command.robot_communication_event.DONE, this, &TaskManager::DONE_Listener);
    myEventManager->subscribe(command.robot_communication_event.ACK, this, &TaskManager::ACK_Listener);
    myEventManager->subscribe(command.robot_communication_event.ERROR, this, &TaskManager::ERROR_Listener);
    myEventManager->subscribe(command.robot_event.updateBase, this, &TaskManager::Robot_UpdateBase_Listener);

    myEventManager->subscribe(command.tooling_event.testPASS, this, &TaskManager::Tooling_TestPass_Listener);
    myEventManager->subscribe(command.tooling_event.testFAIL, this, &TaskManager::Tooling_TestFail_Listener);
    myEventManager->subscribe(command.tooling_event.timeoutFail, this, &TaskManager::Tooling_TimeoutFail_Listener);
    myEventManager->subscribe(command.tooling_event.boot, this, &TaskManager::Tooling_Boot_Listener);
    myEventManager->subscribe(command.tooling_event.Idle, this, &TaskManager::Tooling_Idle_Listener);

    myEventManager->subscribe(command.ccd_communication_event.ACK, this, &TaskManager::ACK_Listener);
    myEventManager->subscribe(command.ccd_communication_event.DONE, this, &TaskManager::DONE_Listener);   
    myEventManager->subscribe(command.ccd_event.scanError, this, &TaskManager::CCD_ScanError_Listener);

    myEventManager->subscribe(command.task_event.Error, this, &TaskManager::ERROR_Listener);
    myEventManager->subscribe(command.task_event.workList_DONE_Add, this, &TaskManager::Task_workList_DONE_Add);
    //DoneList add 處理next Task

}

TaskManager::~TaskManager()
{
    delete logFile;
}

void TaskManager::ACK_Listener(const EventMessage& msg)
{
    //比對任務ID,將等待列表內的任務丟到處理中列表
    for(int i = 0; i < Widget::workList_Waiting.length(); i++)
    {
        if(msg.ID == Widget::workList_Waiting.at(i).ID)
        {
            Widget::workList_InAction.append(Widget::workList_Waiting.takeAt(i));
            fireEvent(command.task_event.workList_Waiting_Removed, msg);
            fireEvent(command.task_event.workList_InAction_Add, msg);
        }
    }
}

void TaskManager::DONE_Listener(const EventMessage& msg)
{
    //比對任務ID,將處理中列表內的任務丟到動作完畢列表
    for(int i = 0; i < Widget::workList_InAction.length(); i++)
    {
        if(msg.ID == Widget::workList_InAction.at(i).ID)
        {
            Widget::workList_Done.append(Widget::workList_InAction.takeAt(i));
            fireEvent(command.task_event.workList_InAction_Removed, msg);
            fireEvent(command.task_event.workList_DONE_Add, msg);
        }
    }
}

void TaskManager::ERROR_Listener(const EventMessage& msg)
{
    for(int i = 0; i < Widget::workList_InAction.length(); i++)
    {
        if(msg.ID == Widget::workList_InAction.at(i).ID)
        {
            Task task = Widget::workList_InAction.takeAt(i);
            task.command = command.robot_command.trayLoadEmpty;
            Widget::workList_Done.append(task);

            if(task.targetID != 0)
            {
                EventMessage newMsg(task.command, task.targetID, EventMessage::NOACK, EventMessage::FromRobot);
                fireEvent(command.tooling_event.Idle, newMsg);
            }

            fireEvent(command.task_event.workList_InAction_Removed, msg);
            fireEvent(command.task_event.workList_DONE_Add, msg);
        }
    }
}


void TaskManager::Tooling_Boot_Listener(const EventMessage &msg)
{
    //GUI 機台開機顯示
}

void TaskManager::Tooling_TestPass_Listener(const EventMessage &msg)
{
    Task *taskPowerOff = new Task(Task::Tooling, command.tooling_command.powerOff);
    taskPowerOff->targetID = msg.toolingNum;
    QThread::msleep(100);

    Widget::workList_Waiting.append(*taskPowerOff);

    Task *taskToPASS = new Task(Task::Robot, command.robot_command.toPASS);
    taskToPASS->targetID = msg.toolingNum;
    QThread::msleep(100);

    Task *taskUpdateTray = new Task(Task::Robot, command.robot_command.updateTray);
    taskUpdateTray->targetID = 0;
    QThread::msleep(100);

    taskToPASS->Next(taskUpdateTray);

    Widget::workList_Waiting.append(*taskToPASS);

    delete taskPowerOff;
    delete taskToPASS;

    fireEvent(command.task_event.workList_Waiting_Add, msg);
}

void TaskManager::Tooling_TestFail_Listener(const EventMessage &msg)
{    
    Task *taskPowerOff = new Task(Task::Tooling, command.tooling_command.powerOff);
    taskPowerOff->targetID = msg.toolingNum;
    QThread::msleep(100);

    Widget::workList_Waiting.append(*taskPowerOff);

    Task *taskToFAIL = new Task(Task::Robot, command.robot_command.toFAIL);
    taskToFAIL->targetID = msg.toolingNum;
    QThread::msleep(100);

    Task *taskUpdateTray = new Task(Task::Robot, command.robot_command.updateTray);
    taskUpdateTray->targetID = 0;
    QThread::msleep(100);

    taskToFAIL->Next(taskUpdateTray);

    Widget::workList_Waiting.append(*taskToFAIL);

    delete taskPowerOff;
    delete taskToFAIL;

    fireEvent(command.task_event.workList_Waiting_Add, msg);
}

void TaskManager::Tooling_TimeoutFail_Listener(const EventMessage &msg)
{
    Task *taskPowerOff = new Task(Task::Tooling, command.tooling_command.powerOff);
    taskPowerOff->targetID = msg.toolingNum;
    QThread::msleep(100);

    Widget::workList_Waiting.append(*taskPowerOff);

    Task *taskToFAIL = new Task(Task::Robot, command.robot_command.toFAIL);
    taskToFAIL->targetID = msg.toolingNum;
    QThread::msleep(100);

    Task *taskUpdateTray = new Task(Task::Robot, command.robot_command.updateTray);
    taskUpdateTray->targetID = 0;
    QThread::msleep(100);

    taskToFAIL->Next(taskUpdateTray);

    Widget::workList_Waiting.append(*taskToFAIL);

    delete taskPowerOff;
    delete taskToFAIL;

    fireEvent(command.task_event.workList_Waiting_Add, msg);
}


void TaskManager::Tooling_Idle_Listener(const EventMessage &msg)
{
    int _targetID = msg.toolingNum;

    Task *taskScanSN = new Task(Task::Robot,command.robot_command.toScanSN);
    taskScanSN->targetID = _targetID;
    QThread::msleep(100);

    Task *taskStartScanSN = new Task(Task::CCD, command.ccd_command.startScanSN);
    taskStartScanSN->targetID = _targetID;
    QThread::msleep(100);

    Task *taskScanMAC = new Task(Task::Robot, command.robot_command.toScanMAC);
    taskScanMAC->targetID = _targetID;
    QThread::msleep(100);

    Task *taskStartScanMAC = new Task(Task::CCD, command.ccd_command.startScanMAC);
    taskStartScanMAC->targetID = _targetID;
    QThread::msleep(100);

    Task *taskToTooling = new Task(Task::Robot, command.robot_command.toTooling);
    taskToTooling->targetID = _targetID;
    QThread::msleep(100);

    Task *taskPowerOn = new Task(Task::Tooling, command.tooling_command.powerOn);
    taskPowerOn->targetID = _targetID;
    QThread::msleep(100);

    Task *taskUpdateTray = new Task(Task::Robot, command.robot_command.updateTray);
    taskUpdateTray->targetID = 0;
    QThread::msleep(100);

    taskScanSN->Next(taskStartScanSN)
              ->Next(taskScanMAC)
              ->Next(taskStartScanMAC)
              ->Next(taskToTooling)
              ->Next(taskPowerOn)
              ->Next(taskUpdateTray);

    Widget::workList_Waiting.prepend(*taskScanSN);

    delete taskScanSN;

    fireEvent(command.task_event.workList_Waiting_Add, msg);
}

void TaskManager::Robot_UpdateBase_Listener(const EventMessage &msg)
{
    Task *taskUpdateBase1 = new Task(Task::Robot,command.robot_command.updateBase1);
    taskUpdateBase1->targetID = 1;
    QThread::msleep(100);

    Task *taskUpdateBase2 = new Task(Task::Robot, command.robot_command.updateBase2);
    taskUpdateBase2->targetID = 2;
    QThread::msleep(100);

    Task *taskUpdateBase3 = new Task(Task::Robot, command.robot_command.updateBase3);
    taskUpdateBase3->targetID = 3;
    QThread::msleep(100);

    taskUpdateBase1->Next(taskUpdateBase2)->Next(taskUpdateBase3);

    Widget::workList_Waiting.prepend(*taskUpdateBase1);

    delete taskUpdateBase1;

    fireEvent(command.task_event.workList_Waiting_Add, msg);
}

void TaskManager::CCD_ScanError_Listener(const EventMessage &msg)
{
    Task* taskToFAIL = new Task(Task::Robot, command.robot_command.toScanFAIL);
    taskToFAIL->targetID = msg.toolingNum;
    QThread::msleep(100);

    Task *taskUpdateTray = new Task(Task::Robot, command.robot_command.updateTray);
    taskUpdateTray->targetID = 0;
    QThread::msleep(100);

    taskToFAIL->Next(taskUpdateTray);

    delete Widget::workList_InAction.first().nextTask;

    Widget::workList_InAction.first().Next(taskToFAIL);

//    Task* taskToScanSN = new Task(Task::Robot, command.robot_command.toScanSN);
//    taskToScanSN->targetID = msg.toolingNum;
//    Widget::workList_Waiting.prepend(*taskToScanSN);
//    delete taskToScanSN;    
//    fireEvent(command.task_event.workList_Waiting_Add, msg);
}

void TaskManager::Task_workList_DONE_Add(const EventMessage &msg)
{
    recordLog();
    clearDoneList();
    Task doneTask = Widget::workList_Done.last();

    fireEvent(command.tooling_event.takeOut, msg);

    if(doneTask.command == command.robot_command.trayLoadEmpty)
    {
        Widget::systemOn = false;
        fireEvent(command.robot_event.trayLoadEmptyStop, msg);
//        Robot::trayLoadEmptyMode = true;
//        qDebug() << "trayLoadEmptyMode = true";
        delete doneTask.nextTask;
    }
    else if(doneTask.nextTask != nullptr)
    {
        Task nextTask = *doneTask.nextTask;
        Widget::workList_Waiting.prepend(nextTask);
        delete doneTask.nextTask;
        fireEvent(command.task_event.workList_Waiting_Add, msg);
    }

    Robot::ActionIdle = true;
}

void TaskManager::clearDoneList()
{
    if(Widget::workList_Done.length() > 20)
    {
        Widget::workList_Done.removeFirst();
    }

    EventMessage msg;
    fireEvent(command.task_event.workList_DONE_Removed, msg);
}

void TaskManager::recordLog()
{
    Task task = Widget::workList_Done.last();
    QTextStream out(logFile);
    out << "Time    : " << QTime::currentTime().toString() << endl
        << "Command : " << task.command << endl
        << "TargetID: " << QString::number(task.targetID) << endl
        << "-------------------------------------------------------" << endl;
}
