#include "startupsetting.h"
#include "QSettings"

StartUpSetting::StartUpSetting(QObject *parent) : QObject(parent)
{
    offsetList =  QVector<Base>(3);
    readSetting();
    readBaseSetting();

}

void StartUpSetting::readSetting()
{
    QSettings setting("Setting.ini",QSettings::IniFormat);
    port = setting.value("Option/Port").toInt();
    robotIP = setting.value("Option/RobotIP").toString();
    robotPort = setting.value("Option/RobotPort").toInt();     
}

void StartUpSetting::readBaseSetting()
{
    offsetList.clear();
    offsetList.resize(3);

    QSettings baseIni("Base_Setting.ini", QSettings::IniFormat);

    QList<int> matchBase;

    matchBase.append(baseIni.value("BaseMatch/Base1").toInt());
    matchBase.append(baseIni.value("BaseMatch/Base2").toInt());
    matchBase.append(baseIni.value("BaseMatch/Base3").toInt());

    QStringList baseListIni = baseIni.childGroups();

    for(int i = 0; i < matchBase.length(); i++)
    {
        baseIni.beginGroup(baseListIni.at(matchBase.at(i)));

        QStringList baseKey = baseIni.childKeys();

        Base base;
        base.ID = QString::number(matchBase.at(i));
        for(int c = 0; c < baseKey.length(); c++)
        {
            if(baseKey.at(c) == "X")
            {
                base.X = baseIni.value("X").toString();
            }else if(baseKey.at(c) == "Y")
            {
                base.Y = baseIni.value("Y").toString();
            }else if(baseKey.at(c) == "Z")
            {
                base.Z = baseIni.value("Z").toString();
            }else if(baseKey.at(c) == "A")
            {
                base.A = baseIni.value("A").toString();
            }else if(baseKey.at(c) == "B")
            {
                base.B = baseIni.value("B").toString();
            }else if(baseKey.at(c) == "C")
            {
                base.C = baseIni.value("C").toString();
            }else if(baseKey.at(c) == "SN")
            {
                base.SN = baseIni.value("SN").toString();
                base.type = base.SN.section('-', 1, 1);
            }else if(baseKey.at(c) == "Width")
            {
                base.width = baseIni.value("Width").toString();
            }
        }
        offsetList[i] = base;

        baseIni.endGroup();
    }
}

void StartUpSetting::readModuleSetting()
{
    QSettings moduleSetting("Module_Setting.ini", QSettings::IniFormat);

}

void StartUpSetting::updateBaseSetting(const QVector<Base> &_baseList)
{
    QSettings baseIni("Base_Setting.ini", QSettings::IniFormat);
    baseIni.setValue("BaseMatch/Base1", _baseList.at(0).ID);
    baseIni.setValue("BaseMatch/Base2", _baseList.at(1).ID);
    baseIni.setValue("BaseMatch/Base3", _baseList.at(2).ID);

    readBaseSetting();
}

void StartUpSetting::writeBaseSetting()
{

}
