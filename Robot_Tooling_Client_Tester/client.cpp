#include "client.h"
#include <QCoreApplication>

QT_USE_NAMESPACE

Client::Client(const QString &_SN, const QString &_MAC, QObject *parent) :
    SN(_SN), MAC1(_MAC), QObject(parent)
{
    readIniFile();

    //initialize Serial port
    serial = new QSerialPort;
    connect(serial, SIGNAL(readyRead()), this, SLOT(readyRead_serial()));
    serial->setPortName(com);
    serial->setBaudRate(QSerialPort::Baud57600);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);

    //initailize Timer
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutForBoot()));

    openSerialPort();

}

Client::~Client()
{
    delete serial;
    delete timer;
}

void Client::readIniFile()
{
    QSettings setting("Setting.ini",QSettings::IniFormat);
    com = setting.value("Option/COMPortName").toString();
    timerSecond_checkOnline = setting.value("Option/Timer_check(sec)").toInt();
}

void Client::openSerialPort()
{
    if(!serial->open(QIODevice::ReadWrite))
    {
        qDebug() << "SerialPort can't open.";

        exit(1);
       // QCoreApplication::exit(1);
    }else
    {
        qDebug() << "SerialPort is open.";

        timerCounter = 0;
        timer->start(1000);
        qDebug() << "Timer Start";
    }
}

void Client::readyRead_serial()
{  
    static QByteArray dataBuffer;

    dataBuffer.append(serial->readAll());

    qDebug() << "dataBuffer << " + dataBuffer;

    //DOS Boot
    if(dataBuffer.contains(";"))
    {
        qDebug() << "data << " + dataBuffer;
        if(dataBuffer.contains("PASS"))
        {
            qDebug() << "Test pass";
            timer->stop();

            dataBuffer.clear();
            exit(1);
        }else if(dataBuffer.contains("FAIL"))
        {
            qDebug() << "Test fail";
            timer->stop();

            dataBuffer.clear();
            exit(1);
        }else
        {
            timerCounter = 0;

            serial->write("1");
            qDebug() << "SendToDOS >> 1";
            dataBuffer.remove(dataBuffer.length()-1,1);
            qDebug() << "TestStage >> " + dataBuffer;
        }
        dataBuffer.clear();
    }
    //SN request
    else if(dataBuffer.contains(0xBC))
    {
        serial->write("B");
        qDebug() << "SendToDOS >> B";

        dataBuffer.clear();
    }
    //SN request
    else if(dataBuffer.contains(0x07))
    {
        QString sendData = SN + "1" + MAC1 + "                          "; // 26 spaces for Jastin.
        serial->write(sendData.toLocal8Bit().data());
        qDebug() << "SendToDOS >> " + sendData;

        dataBuffer.clear();
    }
}

void Client::timeoutForBoot()
{
    timerCounter++;
    if(timerCounter % 5 == 0)
        qDebug() << QString::number(timerCounter) + "Second...";

    if(timerCounter <= timerSecond_checkOnline)
        return;

    qDebug() << "Timeout fail";

    exit(1);

    timer->stop();
    timerCounter = 0;
}
