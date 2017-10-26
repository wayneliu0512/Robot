#include "tooling.h"
#include "widget.h"

Tooling::Tooling(int _toolingNum)
{
    toolingNum = _toolingNum;
    //socket = new QTcpSocket;

    state = Tooling::OFFLINE;
    testTime = TestTime::FIRST_TEST;

    communication = new Tooling_Communication(toolingNum);

    msgBox.setStandardButtons(QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle("Warning");

    EventManager *myEventManager = EventManager::Instance();
    myEventManager->subscribe(command.tooling_communication_event.NoACK, this, &Tooling::No_ACK_Event_Listener);
//    myEventManager->subscribe(command.task_event.workList_DONE_Add, this, &Tooling::Tooling_Idle_Fire);
    myEventManager->subscribe(command.tooling_event.takeOut, this, &Tooling::Tooling_Idle_Fire);
    myEventManager->subscribe(command.tooling_event.powerOn, this, &Tooling::powerOn_Listener);
    myEventManager->subscribe(command.tooling_event.powerOff, this, &Tooling::powerOff_Listener);
    myEventManager->subscribe(command.tooling_event.AirUp, this, );
    myEventManager->subscribe(command.tooling_event.AirDown, this, );
    myEventManager->subscribe(command.tooling_event.sendSocket, this, &Tooling::sendSocket_Listener);

}

Tooling::~Tooling()
{
    delete communication;
    //delete socket;
}

//設定socket
void Tooling::setSocket(QTcpSocket *tcpsocket)
{
    connect(communication, SIGNAL(update(Tooling_Communication::State)),
            this, SLOT(updateConnectionState(Tooling_Communication::State)));
    communication->setSocket(tcpsocket);

    EventMessage msg(command.robot_command.toPASS, toolingNum, EventMessage::NOACK, EventMessage::FromRobot);
    fireEvent(command.tooling_event.Idle,msg);

    QThread::msleep(100);
}

void Tooling::sendSocket_Listener(const EventMessage &msg)
{
    if(msg.toolingNum == toolingNum)
        communication->sendData(msg.data);
}

//非ACK型的socket監聽
void Tooling::No_ACK_Event_Listener(const EventMessage &msg)
{
    if(msg.objectType == EventMessage::FromTooling && msg.toolingNum == toolingNum)
    {
        QString str = msg.data;

        if(str == "test pass")
        {
            if(Tooling::testTime == Tooling::FIRST_TEST)
            {
                testTime = Tooling::SECOND_TEST;
                fireEvent(command.tooling_event.reTest, msg);
            }else
            {
                fireEvent(command.tooling_event.testPASS, msg);
            }

        }else if(str == "test fail")
        {
            if(Tooling::testTime == Tooling::FIRST_TEST)
            {
                testTime = Tooling::SECOND_TEST;
                fireEvent(command.tooling_event.reTest, msg);
            }else
            {
                testTime = Tooling::FIRST_TEST;
                fireEvent(command.tooling_event.testFAIL, msg);
            }

        }else if(str == "boot")
        {
            fireEvent(command.tooling_event.boot, msg);

        }else if(str == "timeout fail")
        {
            if(Tooling::testTime == Tooling::FIRST_TEST)
            {
                testTime = Tooling::SECOND_TEST;
                fireEvent(command.tooling_event.reTest, msg);
            }else
            {
                testTime = Tooling::FIRST_TEST;
                fireEvent(command.tooling_event.timeoutFail, msg);
            }

        }else if(str.contains("ERROR"))
        {
            fireEvent(command.tooling_event.testFAIL, msg);
//            fireEvent(command.task_event.Error, msg);

        }
    }
}

// 監聽 workList_DONE_Add 事件 , 若是自己這個機台 且 DONE任務是 toPASS 或 toFAIL 則此機台Idle , 觸發機台Idle事件
void Tooling::Tooling_Idle_Fire(const EventMessage &msg)
{
    Task task = Widget::workList_Done.last();
    if(task.targetID != toolingNum)
    {
        return;
    }
    if((task.command == command.robot_command.toPASS) || (task.command == command.robot_command.toFAIL)
       || (task.command == command.robot_command.toScanFAIL))
    {
        EventMessage newMsg(task.command, toolingNum, EventMessage::NOACK, EventMessage::FromRobot);
        fireEvent(command.tooling_event.Idle, newMsg);
    }
}

void Tooling::timeoutFailFire()
{
    EventMessage msg(command.robot_command.toFAIL, toolingNum, EventMessage::NOACK, EventMessage::FromTooling);
    fireEvent(command.tooling_event.timeoutFail,msg);
}

//機箱 Power On
void Tooling::powerOn_Listener(const EventMessage &msg)
{
    if(msg.task->targetID != toolingNum)
    {
        return;
    }

    switch (toolingNum) {
    case 1:
        //Prepare SN, MAC to send
        QString sendData = CCD::tooling1_SN + ";" + CCD::tooling1_MAC;
        break;
    case 2:
        //Prepare SN, MAC to send
        QString sendData = CCD::tooling2_SN + ";" + CCD::tooling2_MAC;
        break;
    case 3:
        //Prepare SN, MAC to send
        QString sendData = CCD::tooling3_SN + ";" + CCD::tooling3_MAC;
        break;

    default:
        QMessageBox::critical(this, tr("Warning"), tr("Error: Tooling::PowerOn_Listener"));
        break;
    }

    //Send data to tooling
    communication->sendData(sendData);

    fireEvent(command.robot_event.ActionTask, msg);
    updateState(Tooling::START_TESTING);
}

//機箱 Power Off
void Tooling::powerOff_Listener(const EventMessage &msg)
{
    if(msg.task->targetID != toolingNum)
    {
        return;
    }

    fireEvent(command.robot_event.ActionTask, msg);
    updateState(Tooling::ONLINE);
}

//更新connection 的狀態
void Tooling::updateConnectionState(Tooling_Communication::State _state)
{
    switch(_state)
    {
    case Tooling_Communication::OFFLINE:
        updateState(Tooling::OFFLINE);
        break;
    case Tooling_Communication::ONLINE:
        updateState(Tooling::ONLINE);
        break;
    }
}
