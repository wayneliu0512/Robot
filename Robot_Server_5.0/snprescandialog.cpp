#include "snprescandialog.h"
#include "ui_snprescandialog.h"


SNpreScanDialog::SNpreScanDialog(StartUpSetting *_setting, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SNpreScanDialog),setting(_setting)
{
    ui->setupUi(this);

    newOffsetList = QVector<Base>(3);
}

SNpreScanDialog::~SNpreScanDialog()
{
    delete ui;
}

void SNpreScanDialog::keyInFinished(Phase _phase)
{
    switch(_phase)
    {
    case TOOLING1:
        //如果groupBox 有一個 lineEdit 是空的,就跳出不做任何判斷
        if(ui->lineEdit_Tooling_1->text().isEmpty() || ui->lineEdit_Base_1->text().isEmpty() || 
           ui->lineEdit_ModuleBase_1->text().isEmpty() || ui->lineEdit_Module_1->text().isEmpty())
            return;
        
        //對groupBox 裡的4組條碼做防呆判斷, if PASS = 開啟groupBox2
        if(verifyInfoIsPass(groupBoxData))
        {
            ui->groupBox->setEnabled(false);  
            ui->groupBox_2->setEnabled(true);
            ui->lineEdit_Tooling_2->setFocus();
        }

        break;
        
    case TOOLING2:
        //如果groupBox 有一個 lineEdit 是空的,就跳出不做任何判斷
        if(ui->lineEdit_Tooling_2->text().isEmpty() || ui->lineEdit_Base_2->text().isEmpty() || 
           ui->lineEdit_ModuleBase_2->text().isEmpty() || ui->lineEdit_Module_2->text().isEmpty())
            return;
        
        //對groupBox 裡的4組條碼做防呆判斷, if PASS = 開啟groupBox3
        if(verifyInfoIsPass(groupBoxData))
        {
            ui->groupBox_2->setEnabled(false);  
            ui->groupBox_3->setEnabled(true);
            ui->lineEdit_Tooling_3->setFocus();
        }
        
        break;
        
    case TOOLING3:
        //如果groupBox 有一個 lineEdit 是空的,就跳出不做任何判斷
        if(ui->lineEdit_Tooling_3->text().isEmpty() || ui->lineEdit_Base_3->text().isEmpty() ||
           ui->lineEdit_ModuleBase_3->text().isEmpty() || ui->lineEdit_Module_3->text().isEmpty())
            return;

        //對groupBox 裡的4組條碼做防呆判斷, if PASS = 更新baseList
        if(verifyInfoIsPass(groupBoxData))
        {
            ui->groupBox_3->setEnabled(false);
            setting->updateBaseSetting(newOffsetList);
            newOffsetList[2] = adjustTooling3Offset(newOffsetList[2]);
            this->accept();
        }
        break;
    }
}

void SNpreScanDialog::closeEvent(QCloseEvent *event)
{
    //跳出警告視窗, if cancel 就忽視視窗關閉
    if(QMessageBox::Cancel == QMessageBox::warning(nullptr, "Warning", "Are you sure you don't want to change Base_setting", QMessageBox::Cancel, QMessageBox::Ok))
    {
        event->ignore();
    }else
    {
        newOffsetList = setting->offsetList;
        newOffsetList[2] = adjustTooling3Offset(newOffsetList[2]);
        event->accept();
    }
}

bool SNpreScanDialog::verifyInfoIsPass(const GroupBoxData &_groupbox)
{
    Base offset;

    //檢查ini檔裡是否有此序號
    for(int i = 0 ; i < setting->offsetList.length() ; i++)
    {
        if(setting->offsetList.at(i).SN == _groupbox.tooling)
        {
            offset = setting->offsetList.at(i);
            break;
        }
    }

    //檢查ini檔裡是否有此序號
    if(offset.ID.isEmpty())
    {
        QMessageBox::critical(nullptr, "Error", "There's no tooling SN to match", QMessageBox::Cancel, QMessageBox::Ok);
        return false;
    }

    //檢查模組座位置跟base位置是否吻合
    if(_groupbox.moduleBase != _groupbox.base)
    {
        QMessageBox::critical(nullptr, "Error", "Module base can't match base", QMessageBox::Cancel, QMessageBox::Ok);
        return false;
    }

    //檢查模組機種是否與機箱機種吻合
    if(!_groupbox.module.section('-', 1, 1).contains(offset.type))
    {
        QMessageBox::critical(nullptr, "Error", "Module type can't match tooling type", QMessageBox::Cancel, QMessageBox::Ok);
        return false;
    }

    //檢查每組機箱序號沒有重複到
    for(int i = 0; i < newOffsetList.length(); i++)
    {
        if(newOffsetList.at(i).SN == _groupbox.tooling)
        {
            QMessageBox::critical(nullptr, "Error", "tooling SN conflict", QMessageBox::Cancel, QMessageBox::Ok);
            return false;
        }
    }

    //檢查每組模組序號沒有重複到
    if(moduleList.contains(_groupbox.module))
    {
        QMessageBox::critical(nullptr, "Error", "module SN conflict", QMessageBox::Cancel, QMessageBox::Ok);
        return false;
    }

    //檢查此base位置是否已經有擺放東西
    if(!newOffsetList.at(_groupbox.base.toInt()-1).ID.isEmpty())
    {
        QMessageBox::critical(nullptr, "Error", "Base conflict", QMessageBox::Cancel, QMessageBox::Ok);
        return false;
    }
    else
    {        
        //將檢查pass的offset加入新的offsetList
        newOffsetList[_groupbox.base.toInt()-1] = offset;

        //暫存Module 序號 比對預防衝突用
        moduleList.append(_groupbox.module);
        return true;
    }
}

Base SNpreScanDialog::adjustTooling3Offset(Base _offset)
{
    //第三個機台位置,因為他的定位點在另一邊,所以要調整偏移量
    _offset.Y = QString::number(_offset.Y.toDouble() + _offset.width.toDouble());

    return _offset;
}

void SNpreScanDialog::on_lineEdit_Tooling_1_returnPressed()
{
    QRegExp rx("^FX-[A-Z0-9]*-[0-9]{3,3}$");

    if(!rx.exactMatch(ui->lineEdit_Tooling_1->text()))
    {
        QMessageBox::critical(nullptr, "Error", "Syntax error!", QMessageBox::Cancel, QMessageBox::Ok);
        ui->lineEdit_Tooling_1->clear();
        return;
    }    
    groupBoxData.tooling = ui->lineEdit_Tooling_1->text();

    ui->lineEdit_Base_1->setFocus();

    keyInFinished(TOOLING1);
}

void SNpreScanDialog::on_lineEdit_Base_1_returnPressed()
{
    QRegExp rx("^[0-9]{1,3}$");

    if(!rx.exactMatch(ui->lineEdit_Base_1->text()))
    {
        QMessageBox::critical(nullptr, "Error", "Syntax error!", QMessageBox::Cancel, QMessageBox::Ok);
        ui->lineEdit_Base_1->clear();
        return;
    }

    groupBoxData.base = ui->lineEdit_Base_1->text();

    ui->lineEdit_ModuleBase_1->setFocus();

    keyInFinished(TOOLING1);
}

void SNpreScanDialog::on_lineEdit_ModuleBase_1_returnPressed()
{
    QRegExp rx("^[0-9]{1,3}$");

    if(!rx.exactMatch(ui->lineEdit_ModuleBase_1->text()))
    {
        QMessageBox::critical(nullptr, "Error", "Syntax error!", QMessageBox::Cancel, QMessageBox::Ok);
        ui->lineEdit_ModuleBase_1->clear();
        return;
    }

    groupBoxData.moduleBase = ui->lineEdit_ModuleBase_1->text();

    ui->lineEdit_Module_1->setFocus();

    keyInFinished(TOOLING1);
}

void SNpreScanDialog::on_lineEdit_Module_1_returnPressed()
{
    QRegExp rx("^FX-[A-Z0-9]*-[0-9]{3,3}$");

    if(!rx.exactMatch(ui->lineEdit_Module_1->text()))
    {
        QMessageBox::critical(nullptr, "Error", "Syntax error!", QMessageBox::Cancel, QMessageBox::Ok);
        ui->lineEdit_Module_1->clear();
        return;
    }

    groupBoxData.module = ui->lineEdit_Module_1->text();

    keyInFinished(TOOLING1);
}

void SNpreScanDialog::on_lineEdit_Tooling_2_returnPressed()
{
    QRegExp rx("^FX-[A-Z0-9]*-[0-9]{3,3}$");

    if(!rx.exactMatch(ui->lineEdit_Tooling_2->text()))
    {
        QMessageBox::critical(nullptr, "Error", "Syntax error!", QMessageBox::Cancel, QMessageBox::Ok);
        ui->lineEdit_Tooling_2->clear();
        return;
    }

    groupBoxData.tooling = ui->lineEdit_Tooling_2->text();

    ui->lineEdit_Base_2->setFocus();

    keyInFinished(TOOLING2);
}

void SNpreScanDialog::on_lineEdit_Base_2_returnPressed()
{
    QRegExp rx("^[0-9]{1,3}$");

    if(!rx.exactMatch(ui->lineEdit_Base_2->text()))
    {
        QMessageBox::critical(nullptr, "Error", "Syntax error!", QMessageBox::Cancel, QMessageBox::Ok);
        ui->lineEdit_Base_2->clear();
        return;
    }

    groupBoxData.base = ui->lineEdit_Base_2->text();

    ui->lineEdit_ModuleBase_2->setFocus();

    keyInFinished(TOOLING2);
}

void SNpreScanDialog::on_lineEdit_ModuleBase_2_returnPressed()
{
    QRegExp rx("^[0-9]{1,3}$");

    if(!rx.exactMatch(ui->lineEdit_ModuleBase_2->text()))
    {
        QMessageBox::critical(nullptr, "Error", "Syntax error!", QMessageBox::Cancel, QMessageBox::Ok);
        ui->lineEdit_ModuleBase_2->clear();
        return;
    }

    groupBoxData.moduleBase = ui->lineEdit_ModuleBase_2->text();

    ui->lineEdit_Module_2->setFocus();

    keyInFinished(TOOLING2);
}

void SNpreScanDialog::on_lineEdit_Module_2_returnPressed()
{
    QRegExp rx("^FX-[A-Z0-9]*-[0-9]{3,3}$");

    if(!rx.exactMatch(ui->lineEdit_Module_2->text()))
    {
        QMessageBox::critical(nullptr, "Error", "Syntax error!", QMessageBox::Cancel, QMessageBox::Ok);
        ui->lineEdit_Module_2->clear();
        return;
    }

    groupBoxData.module = ui->lineEdit_Module_2->text();

    keyInFinished(TOOLING2);
}

void SNpreScanDialog::on_lineEdit_Tooling_3_returnPressed()
{
    QRegExp rx("^FX-[A-Z0-9]*-[0-9]{3,3}$");

    if(!rx.exactMatch(ui->lineEdit_Tooling_3->text()))
    {
        QMessageBox::critical(nullptr, "Error", "Syntax error1!", QMessageBox::Cancel, QMessageBox::Ok);
        ui->lineEdit_Tooling_3->clear();
        return;
    }

    groupBoxData.tooling = ui->lineEdit_Tooling_3->text();

    ui->lineEdit_Base_3->setFocus();

    keyInFinished(TOOLING3);
}

void SNpreScanDialog::on_lineEdit_Base_3_returnPressed()
{
    QRegExp rx("^[0-9]{1,3}$");

    if(!rx.exactMatch(ui->lineEdit_Base_3->text()))
    {
        QMessageBox::critical(nullptr, "Error", "Syntax error!", QMessageBox::Cancel, QMessageBox::Ok);
        ui->lineEdit_Base_3->clear();
        return;
    }

    groupBoxData.base = ui->lineEdit_Base_3->text();

    ui->lineEdit_ModuleBase_3->setFocus();

    keyInFinished(TOOLING3);
}

void SNpreScanDialog::on_lineEdit_ModuleBase_3_returnPressed()
{
    QRegExp rx("^[0-9]{1,3}$");

    if(!rx.exactMatch(ui->lineEdit_ModuleBase_3->text()))
    {
        QMessageBox::critical(nullptr, "Error", "Syntax error!", QMessageBox::Cancel, QMessageBox::Ok);
        ui->lineEdit_ModuleBase_3->clear();
        return;
    }

    groupBoxData.moduleBase = ui->lineEdit_ModuleBase_3->text();

    ui->lineEdit_Module_3->setFocus();

    keyInFinished(TOOLING3);
}

void SNpreScanDialog::on_lineEdit_Module_3_returnPressed()
{
    QRegExp rx("^FX-[A-Z0-9]*-[0-9]{3,3}$");

    if(!rx.exactMatch(ui->lineEdit_Module_3->text()))
    {
        QMessageBox::critical(nullptr, "Error", "Syntax error!", QMessageBox::Cancel, QMessageBox::Ok);
        ui->lineEdit_Module_3->clear();
        return;
    }

    groupBoxData.module = ui->lineEdit_Module_3->text();

    keyInFinished(TOOLING3);
}

