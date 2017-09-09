#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QObject>
#include <QtCore>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <task.h>
#include <base.h>
#include <command.h>
#include <taskmanager.h>
#include <actionmanager.h>
#include <event/EventManager.h>
#include <CCD/ccd.h>
#include <CCD/ccd_gui.h>
#include <Robot/robot.h>
#include <Robot/robot_gui.h>
#include <Tooling/tooling.h>
#include <Tooling/tooling_gui.h>
#include <startupsetting.h>

namespace Ui {
class Widget;

}

using namespace Mage;

class Widget : public QWidget
{
    Q_OBJECT

public: 

    explicit Widget(QWidget *parent = 0);
    ~Widget();
    //等待執行任務列表
    static QList<Task> workList_Waiting;
    //處理中任務列表
    static QList<Task> workList_InAction;
    //動作完畢任務列表
    static QList<Task> workList_Done;

    static bool systemOn;

    static int flashCounter;

    QTimer *flashTimer;

private:

    Ui::Widget *ui;

    QTcpServer *server;

    QTcpSocket *socket;

    StartUpSetting *setting;

    Tooling *tooling_1, *tooling_2, *tooling_3;    
    Tooling_GUI *tooling_GUI_1, *tooling_GUI_2, *tooling_GUI_3;

    Robot *robot;
    Robot_GUI *robot_GUI;

    CCD *ccd;
    CCD_GUI *ccd_GUI;

    Command command;

    TaskManager* taskManager;

    ActionManager* actionManager;

    QMessageBox msgBox;

//    QList<QTcpSocket*> socketList;

    void sendRobotBaseInfo();

    void serverOn(int _port);

    //創建所以程式需要事件
    void createAllEvent();

    //列表顯示Table (等待執行任務列表)(Debug用)
    void changeTable1();
    //列表顯示Table (處理中任務列表)(Debug用)
    void changeTable2();
    //列表顯示Table (動作完畢任務列表)(Debug用)
    void changeTable3();

    //最激歪的兩個位置,y要先加上機箱寬度再送出
    void updateTable(const EventMessage& msg);

    void fireEvent(const QString& str, const EventMessage& msg) {
      // Fire the event and all the subscribed class methods will get called.
      EventManager *myEventManager = EventManager::Instance();
      myEventManager->execute(str, msg);
    }

private slots:

    void newConnection();
    void readyRead();

    //GUI 觸發
    void on_Button_Start_clicked();
    void on_Button_Stop_clicked();   
    void on_comboBox_activated(const QString &arg1);

    //用於閃爍的計時器
    void flashingTimerReset();
};

#endif // WIDGET_H
