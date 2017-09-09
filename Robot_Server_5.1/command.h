#ifndef COMMAND_H
#define COMMAND_H
#include <QString>

class Command
{
public:
    Command();

    //手臂要執行的任務類型
    struct Robot_Command
    {
        QString toScanSN = "Robot_toScan_ActionType";
        QString toScanMAC = "Robot_toScanMAC_ActionType";
        QString toScanFAIL = "Robot_toScanFAIL_ActionType";
        QString toTooling = "Robot_toTooling_ActionType";
        QString toBox = "Robot_toBox_ActionType";
        QString toPASS = "Robot_toPASS_ActionType";
        QString toFAIL = "Robot_toFAIL_ActionType";
        QString toReTest = "Robot_toReTest_ActionType";
        QString updateBase1 = "Robot_updateBase1_ActionType";
        QString updateBase2 = "Robot_updateBase2_ActionType";
        QString updateBase3 = "Robot_updateBase3_ActionType";
        QString updateTray = "Robot_updateTray_ActionType";
    };

    //有關 Robot 的事件類型
    struct Robot_event
    {
        //手臂動作閒置時觸發
        QString ActionIdle = "Robot_ActionIdle_Event";
        //手臂非動作任務閒置時觸發
        QString NonActionIdle = "Robot_NonActionIdle_Event";
        //手臂動作時觸發
        QString Busy = "Robot_Busy_Event";
        //叫手臂執行動作型任務
        QString ActionTask = "Robot_ActionTask_Event";
        //叫手臂執行非動作型任務
        QString NonActionTask = "Robot_NonActionTask_Event";
        //叫手臂更新Base
        QString updateBase= "Robot_UpdateBase_Event";
    };

    //有關Robot 通訊的事件類型
    struct Robot_Communication_event
    {
        //收到ACK回復時觸發(ACK:確認訊息接收到的機制)
        QString ACK = "Robot_ACK_Event";
        //收到DONE回復時觸發(動作以外的任務處理完畢時)
        QString DONE = "Robot_DONE_Event";
    };

    //機箱要執行的任務類型
    struct Tooling_Command
    {
        //機箱開機
        QString powerOn = "Tooling_PowerOn_ActionType";
        //機箱關機
        QString powerOff = "Tooling_PowerOff_ActionType";
    };

    //有關Tooling的事件類型
    struct Tooling_event
    {
        //機箱測試完畢PASS
        QString testPASS = "Tooling_TestPass_Event";
        //機箱測試完畢FAIL
        QString testFAIL = "Tooling_TestFail_Event";
        //機箱測試時間過長(未開機)
        QString timeoutFail = "Tooling_TimeoutFail_Event";
        //機箱開機成功
        QString boot = "Tooling_Boot_Event";
        //機箱內待測物被取出
        QString takeOut = "Tooling_takeOut_Event";
        //機箱閒置
        QString Idle = "Tooling_Idle_Event";
        //機箱開機
        QString powerOn = "Tooling_PowerOn_Event";
        //機箱關機
        QString powerOff = "Tooling_PowerOff_Event";
        //丟Socket給機台
        QString sendSocket = "Tooling_SendSocket_Event";
    };

    //有關Tooling 通訊的事件類型
    struct Tooling_Communication_event
    {
        //收到不是ACK協定的socket時觸發
        QString NoACK = "Tooling_NoACK_Event";
    };

    //有關 Task 的事件類型
    struct Task_event
    {
        //等待列表加入,移除一筆任務時會觸發
        QString workList_Waiting_Add = "workList_Waiting_Add_Event";
        QString workList_Waiting_Removed = "workList_Waiting_Remove_Event";

        //處理中列表加入,移除一筆任務時會觸發
        QString workList_InAction_Add = "workList_InAction_Add_Event";
        QString workList_InAction_Removed = "workList_InAction_Remove_Event";

        //動作完畢列表加入,移除一筆任務時會觸發
        QString workList_DONE_Add = "workList_DONE_Add_Event";
        QString workList_DONE_Removed = "workList_DONE_Remove_Event";
        //系統開始運作
        QString systemOn = "system_On_Event";
        QString Error = "Error_Event";
        QString systemOff = "system_Off_Event";
    };

    //BarcodeScanner 的任務類型
    struct CCD_Command
    {
        //開始ScanSN
        QString startScanSN = "CCD_StartScan_SN_ActionType";
        //開始ScanMAC
        QString startScanMAC = "CCD_StartScan_MAC_ActionType";
    };

    //BarcodeScanner 的事件類型
    struct CCD_event
    {
        QString scanError = "CCD_ScanError_Event";        
        //開始ScanSN
        QString startScanSN = "CCD_StartScanSN_Event";
        //開始ScanMAC
        QString startScanMAC = "CCD_StartScan_Event";
    };

    //有關Robot 通訊的事件類型
    struct CCD_Communication_event
    {
        //收到ACK回復時觸發(ACK:確認訊息接收到的機制)
        QString ACK = "CCD_ACK_Event";
        //收到DONE回復時觸發(動作以外的任務處理完畢時)
        QString DONE = "CCD_DONE_Event";
    };

    Robot_Command robot_command;
    Robot_event robot_event;
    Robot_Communication_event robot_communication_event;
    Tooling_Command tooling_command;
    Tooling_event tooling_event;
    Tooling_Communication_event tooling_communication_event;
    CCD_Command ccd_command;
    CCD_event ccd_event;
    CCD_Communication_event ccd_communication_event;
    Task_event task_event;
};

#endif // COMMAND_H
