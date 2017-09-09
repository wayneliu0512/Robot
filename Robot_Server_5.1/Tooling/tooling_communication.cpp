#include "tooling_communication.h"
#include "QMessageBox"

Tooling_Communication::Tooling_Communication(int _toolingNum)
{
    socket = new QTcpSocket;
    toolingNum = _toolingNum;
}

Tooling_Communication::~Tooling_Communication()
{
    delete socket;
}

void Tooling_Communication::setSocket(QTcpSocket *_socket)
{
    socket = _socket;
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    updateState(Tooling_Communication::ONLINE);
}

void Tooling_Communication::readyRead()
{
    updateState(Tooling_Communication::RECEIVE_NOACK);
    QString str = socket->readAll();
    qDebug() << "ReadFromTooling" + QString::number(toolingNum) + ": " + str;
    EventMessage msg(str, toolingNum, EventMessage::NOACK, EventMessage::FromTooling);
    fireEvent(command.tooling_communication_event.NoACK, msg);
}

void Tooling_Communication::sendData(QString str)
{
    socket->write(str.toLatin1());
    qDebug() << "SendToTooling: " + str;
}

void Tooling_Communication::disconnected()
{
    updateState(Tooling_Communication::OFFLINE);
    qDebug() << "Tooling" + QString::number(toolingNum) + " disconnected!";
}
