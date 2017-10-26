#ifndef STARTUPSETTING_H
#define STARTUPSETTING_H

#include <QObject>
#include <Tooling/tooling.h>
#include <Robot/robot.h>

class StartUpSetting : public QObject
{
    Q_OBJECT
public:
    explicit StartUpSetting(QObject *parent = nullptr);

    ~StartUpSetting(){}

    int port , robotPort;

    QString robotIP;

    QString toolingLogPath;
    //儲存Base座標系的列表 [0]=第一個機台的offset值, [1]=第二個機台的offset值
    QVector<Base> offsetList;

    //更新Base
    void updateBaseSetting(const QVector<Base>& _baseList);

private:

    //讀取ini
    void readSetting();

    //讀取base_setting ini
    void readBaseSetting();

    //讀取module_setting ini
    void readModuleSetting();

    //覆寫base_setting ini
    void writeBaseSetting();
        
};

#endif // STARTUPSETTING_H
