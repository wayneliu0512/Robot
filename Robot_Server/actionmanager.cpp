#include "actionmanager.h"
#include <Robot/robot.h>
#include <widget.h>
#include <snprescandialog.h>

ActionManager::ActionManager()
{
    timer = new QTimer;
    timer->setInterval(1000);

    connect(timer, SIGNAL(timeout()), this, SLOT(ActionManage()));
}

ActionManager::~ActionManager()
{
    delete timer;
}

void ActionManager::start()
{
    Widget::systemOn = true;
    Robot::ActionIdle = true;
    Robot::NonActionIdle = true;
    timer->start();
}

void ActionManager::stop()
{
    Widget::systemOn = false;
    timer->stop();
}

void ActionManager::ActionManage()
{
    if(!Widget::systemOn || Widget::workList_Waiting.empty())
    {
        return;
    }

    if(Robot::ActionIdle)
    {

       dispatch_First_Task();
    }

//    if(TaskManager::comboMode)
//    {
//        if(Robot::ActionIdle && Robot::NonActionIdle)
//        {
//            dispatch_First_Task();
//        }
//        if(Robot::NonActionIdle)
//        {
//            dispatch_First_NonAction_Task();
//        }
//    }else
//    {
//        if(Robot::ActionIdle)
//        {
//            dispatch_First_Action_Task();
//        }
//        if(Robot::NonActionIdle)
//        {
//            dispatch_First_NonAction_Task();
//        }
//    }
}

void ActionManager::dispatch_First_Task()
{
    Task task = Widget::workList_Waiting.first();
    EventMessage messageCarryTask(&task);
    QString commandStr = task.command;

    if(commandStr.contains("ActionType"))
    {
        Robot::ActionIdle = false;
    }else
    {
        Robot::NonActionIdle = false;
    }

    //判斷派發任務對象
    switch(task.target)
    {
    case Task::Robot:
        if(commandStr.contains("ActionType"))
        {
            fireEvent(command.robot_event.ActionTask, messageCarryTask);
        }else
        {
            fireEvent(command.robot_event.NonActionTask, messageCarryTask);
        }
        break;
    case Task::Tooling:
        if(commandStr.contains("On"))
        {
            fireEvent(command.tooling_event.powerOn, messageCarryTask);
        }
        else
        {
            fireEvent(command.tooling_event.powerOff, messageCarryTask);
        }
        break;
    case Task::CCD:
        if(commandStr.contains("SN"))
        {
            fireEvent(command.ccd_event.startScanSN, messageCarryTask);
        }else
        {
            fireEvent(command.ccd_event.startScanMAC, messageCarryTask);
        }
        break;
    case Task::Center:
        //中控程式自己觸發的任務
        break;
    }
}

//void ActionManager::dispatch_First_Action_Task()
//{

//    //開始派發任務
//    for(int i = 0; i < Widget::workList_Waiting.length(); i++)
//    {
//        QString commandStr = Widget::workList_Waiting.at(i).command;
//        //只執行列表中第一個動作型Command
//        if(commandStr.contains("ActionType"))
//        {
//            Robot::ActionIdle = false;
//            Task task = Widget::workList_Waiting.at(i);
//            EventMessage messageCarryTask(&task);
//            fireEvent(command.robot_event.ActionTask, messageCarryTask);
//            break;
//        }
//    }
//}

//void ActionManager::dispatch_First_NonAction_Task()
//{
//    //開始派發任務
//    for(int i = 0; i < Widget::workList_Waiting.length(); i++)
//    {
//        QString commandStr = Widget::workList_Waiting.at(i).command;
//        //只執行列表中第一個非動作型Command
//        if(!commandStr.contains("ActionType"))
//        {
//            Robot::NonActionIdle = false;
//            Task task = Widget::workList_Waiting.at(i);
//            EventMessage messageCarryTask(&task);
//            //判斷派發任務對象
//            switch(task.target)
//            {
//            case Task::Robot:
//                //只執行非動作
//                fireEvent(command.robot_event.NonActionTask, messageCarryTask);
//                break;
//            case Task::Tooling:
//                //目前只有一種任務 所以直接觸發
//                if(commandStr.contains("On"))
//                {
//                    fireEvent(command.tooling_event.powerOn, messageCarryTask);
//                }
//                else
//                {
//                    fireEvent(command.tooling_event.powerOff, messageCarryTask);
//                }
//                break;
//            case Task::CCD:
//                //目前只有一種任務 所以直接觸發
//                if(commandStr.contains("SN"))
//                {
//                    fireEvent(command.ccd_event.startScanSN, messageCarryTask);
//                }else
//                {
//                    fireEvent(command.ccd_event.startScanMAC, messageCarryTask);
//                }
//                break;
//            case Task::Center:
//                //中空程式自己觸發的任務
//                break;
//            }
//            break;
//        }
//    }
//}
