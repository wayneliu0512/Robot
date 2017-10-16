#include "actionmanager.h"
#include <Robot/robot.h>
#include <widget.h>
#include <snprescandialog.h>
#include "Tooling/tooling.h"
#include "Robot/robot.h"
#include <QMessageBox>

ActionManager::ActionManager(Robot *_robot, Tooling *_t1, Tooling *_t2, Tooling *_t3):
    robot(_robot), tooling1(_t1), tooling2(_t2), tooling3(_t3)
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
    if(!Widget::systemOn)
    {
        return;
    }

    if(Robot::ActionIdle)
    {
        if(Robot::trayLoadEmptyMode)
        {
//            if(tooling1->state == Tooling::ONLINE && tooling2->state == Tooling::ONLINE && tooling3->state == Tooling::ONLINE)
//            {
//                Widget::systemOn = false;
//                QMessageBox::information(nullptr, tr("Information"), tr("DisCharge complete."));
//                return;
//            }
            dispatch_OnlyDischarge();
        }else
        {
            dispatch_First_Task();
        }
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

    Robot::ActionIdle = false;

    //判斷派發任務對象
    switch(task.target)
    {
    case Task::Robot:
        fireEvent(command.robot_event.ActionTask, messageCarryTask);
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

void ActionManager::dispatch_OnlyDischarge()
{
    for(int i = 0; i < Widget::workList_Waiting.length(); i++)
    {
        Task task = Widget::workList_Waiting.at(i);
        QString commandStr = task.command;

        switch(task.target)
        {
        case Task::Robot:
            if(commandStr == command.robot_command.toPASS || commandStr == command.robot_command.toFAIL ||
                    commandStr == command.robot_command.lightGreen || commandStr.contains("update"))
            {
                Robot::ActionIdle = false;
                EventMessage messageCarryTask(&task);
                fireEvent(command.robot_event.ActionTask, messageCarryTask);
                return;
            }
            break;
        case Task::Tooling:
            Robot::ActionIdle = false;
            EventMessage messageCarryTask(&task);
            if(commandStr.contains("On"))
            {
                fireEvent(command.tooling_event.powerOn, messageCarryTask);
            }
            else
            {
                fireEvent(command.tooling_event.powerOff, messageCarryTask);
            }
            return;
        }
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
