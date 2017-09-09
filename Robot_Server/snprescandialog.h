#ifndef SNPRESCANDIALOG_H
#define SNPRESCANDIALOG_H

#include <QDialog>
#include <startupsetting.h>
#include <base.h>
#include<QCloseEvent>

namespace Ui {
class SNpreScanDialog;
}

class SNpreScanDialog : public QDialog
{
    Q_OBJECT

public:
    
    //每一個階段, 代表一個groupBox, 也代表一個位置
    enum Phase{ TOOLING1, TOOLING2, TOOLING3 };
    
    explicit SNpreScanDialog(StartUpSetting *_setting, QWidget *parent = 0);
    
    ~SNpreScanDialog();

    //由使用者輸入後, 產生一個新的offsetList
    QVector<Base> newOffsetList;

protected:

    //視窗關閉時觸發事件
    void closeEvent(QCloseEvent *event);

    //當用Esc 來關閉視窗時
    void reject();

private slots:
    
    void on_lineEdit_Tooling_1_returnPressed();

    void on_lineEdit_Base_1_returnPressed();

    void on_lineEdit_ModuleBase_1_returnPressed();

    void on_lineEdit_Module_1_returnPressed();

    void on_lineEdit_Tooling_2_returnPressed();

    void on_lineEdit_Base_2_returnPressed();

    void on_lineEdit_ModuleBase_2_returnPressed();

    void on_lineEdit_Module_2_returnPressed();

    void on_lineEdit_Tooling_3_returnPressed();

    void on_lineEdit_Base_3_returnPressed();

    void on_lineEdit_ModuleBase_3_returnPressed();

    void on_lineEdit_Module_3_returnPressed();

private:
    
    Ui::SNpreScanDialog *ui;
    
    StartUpSetting *setting;

    //先暫存目前輸入的每組模組序號, 用來比對防止他互相重複
    QStringList moduleList;

    //暫存一個groupBox裡面的資料(4組序號)
    struct GroupBoxData
    {
        QString tooling; //Offset
        QString base;
        QString moduleBase;
        QString module;
    };
    
    //暫存一個groupBox裡面的資料(4組序號)
    GroupBoxData groupBoxData;
    
    //完成輸入序號的階段(一個groupBox 代表一個階段)
    void keyInFinished(Phase _phase);
    
    //對一個groupBox裡的4組序號做防呆
    bool verifyInfoIsPass(const GroupBoxData &_groupbox);

    //第三個機台位置,因為他的定位點在另一邊,所以要調整偏移量
    Base adjustTooling3Offset(Base _offset);
};

#endif // SNPRESCANDIALOG_H
