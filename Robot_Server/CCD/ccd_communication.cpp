#include "ccd_communication.h"
#include "CCD/ccd.h"
#include "QJsonObject"
#include "QJsonDocument"
#include <QMessageBox>

CCD_Communication::CCD_Communication(QTcpSocket *_socket)
{
    timer = new QTimer;
    timer->setInterval(5000);
    connect(timer, SIGNAL(timeout()), this, SLOT(ACK_timeout()));

    socket = _socket;
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
}
CCD_Communication::~CCD_Communication()
{
    delete timer;
}

void CCD_Communication::readyRead()
{
    QByteArray readData = socket->readAll();

    QJsonDocument doc = QJsonDocument::fromJson(readData);
    QJsonValue ID_value = doc.object().value("ID");
    QJsonValue type_value = doc.object().value("Type");
    QJsonValue SN_value = doc.object().value("SN");
    QJsonValue MAC_value = doc.object().value("MAC");
    QJsonValue error_value = doc.object().value("Error");
    
    qDebug() << "ReadFromCCD: " + readData;

    if(!error_value.isUndefined())
    {
        qDebug() << "CCD Error << " + error_value.toString();
        EventMessage msg;
        msg.toolingNum = toolingNum;
        fireEvent(command.ccd_event.scanError, msg);
        //fireEvent about reScan or toFAIL
        //return;
    }

    if(type_value.toString() == "ACK")
    {
        if(ID_value.toString() == ACK_ID)
        {
            timer->stop();
            qDebug() << "ACK Back << " + readData;
            updateState(CCD_Communication::RECEIVE_ACK);

            EventMessage msg(ACK_ID, EventMessage::ACK, EventMessage::FromCCD);
            ACK_ID.clear();
            fireEvent(command.ccd_communication_event.ACK, msg);
        }
    }
    else if(type_value.toString() == "DONE")
    {
        if(ID_value.toString() == DONE_ID)
        {
            qDebug() << "DONE Back << " + readData;

            if(!SN_value.isUndefined())
                updateSN(SN_value.toString());

            if(!MAC_value.isUndefined())
                updateMAC(MAC_value.toString());

            updateState(CCD_Communication::RECEIVE_DONE);

            EventMessage msg(DONE_ID, EventMessage::ACK, EventMessage::FromCCD);
            DONE_ID.clear();
            fireEvent(command.ccd_communication_event.DONE, msg);
        }
    }
}

void CCD_Communication::updateSN(const QString &_SN)
{
    switch(toolingNum)
    {
    case 1:
        CCD::tooling1_SN = _SN;
        break;
    case 2:
        CCD::tooling2_SN = _SN;
        break;
    case 3:
        CCD::tooling3_SN = _SN;
        break;
    default:
        QMessageBox::critical(this, tr("Warning"), tr("Error: CCD_Communication/updateSN"));
    }
}

void CCD_Communication::updateMAC(const QString &_MAC)
{
    switch(toolingNum)
    {
    case 1:
        CCD::tooling1_MAC = _MAC;
        break;
    case 2:
        CCD::tooling2_MAC = _MAC;
        break;
    case 3:
        CCD::tooling3_MAC = _MAC;
        break;
    default:
        QMessageBox::critical(this, tr("Warning"), tr("Error: CCD_Communication/updateMAC"));
    }
}

void CCD_Communication::sendSocketToCCD(const QString &_ID, const QString &_CMD, int _toolingNum)
{
    toolingNum = _toolingNum;

    ACK_ID = _ID;
    DONE_ID = _ID;

    QJsonObject ccd_Obj;
    ccd_Obj.insert("ID", _ID);
    ccd_Obj.insert("CMD", _CMD);

    QJsonDocument doc(ccd_Obj);
    
    QByteArray sendData = doc.toJson();

    reSendText = sendData;
  
    //發送資料
    socket->write(sendData);
    qDebug() << "SendToCCD: " + sendData;

    //開始定時重送封包
    timer->start();
}

//ReSend ACK socket
void CCD_Communication::ACK_timeout()
{
    if(ACK_ID.isEmpty())
    {
        timer->stop();
        return;
    }
    socket->write(reSendText);
    qDebug() << "Re SendToCCD: " + reSendText + "......";
}

void CCD_Communication::disconnected()
{
    qDebug() << "CCD disconnected!";
    updateState(CCD_Communication::OFFLINE);
}
