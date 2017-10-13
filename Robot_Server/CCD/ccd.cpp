#include "ccd.h"
#include "QTimer"
#include "QDebug"
#include <QMessageBox>
#include <QLineEdit>
#include <QTcpSocket>
#include "command.h"

QString CCD::SN = "";
QString CCD::MAC = "";

CCD::CCD()
{
    state = CCD::OFFLINE;
    EventManager *myEventManager = EventManager::Instance();
    myEventManager->subscribe(command.ccd_event.startScanSN, this, &CCD::startScanSN_Listener);
    myEventManager->subscribe(command.ccd_event.startScanMAC, this, &CCD::startScanMAC_Listener);
}

CCD::~CCD()
{
    delete communication;
}

void CCD::setSocket(QTcpSocket *_socket)
{
    communication = new CCD_Communication(_socket);
    connect(communication, SIGNAL(update(CCD_Communication::State)), this, SLOT(updateConnectionState(CCD_Communication::State)));
    updateState(CCD::ONLINE);
}

void CCD::startScanSN_Listener(const EventMessage &msg)
{
    if(state == CCD::OFFLINE)
    {
        QMessageBox::critical(nullptr, "Error", "CCD OFFLINE!", QMessageBox::Cancel, QMessageBox::Ok);
        return;
    }

    QString ID = msg.task->ID;
    communication->sendSocketToCCD(ID, "Shot",  msg.task->targetID);
}

void CCD::startScanMAC_Listener(const EventMessage &msg)
{
    if(state == CCD::OFFLINE)
    {
        QMessageBox::critical(nullptr, "Error", "CCD OFFLINE!", QMessageBox::Cancel, QMessageBox::Ok);
        return;
    }

    QString ID = msg.task->ID;
    communication->sendSocketToCCD(ID, "Shot",  msg.task->targetID);
}

void CCD::updateConnectionState(CCD_Communication::State _state)
{
    switch(_state)
    {
    case CCD_Communication::ONLINE:
        updateState(CCD::ONLINE);
        break;
    case CCD_Communication::OFFLINE:
        updateState(CCD::OFFLINE);
        break;
    case CCD_Communication::RECEIVE_ACK:
        updateState(CCD::TAKING_SHOT);
        break;
    case CCD_Communication::RECEIVE_DONE:
        updateState(CCD::FINISH_SHOT);
        break;
    }
}
