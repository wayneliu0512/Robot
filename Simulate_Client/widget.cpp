#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead_socket()));

    qDebug() << "Connecting,..";

    socket->connectToHost("172.20.10.8", 1234);//"192.168.0.103" , "172.16.4.101", "10.211.55.3"
    if(!socket->waitForConnected(1000))
    {
        qDebug() << "Connect Fail";
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::connected()
{
    ui->label->setText("Connected!");
    qDebug() << "Connected!";
    ui->lineEdit->setFocus();
}

void Widget::disconnected()
{
    ui->label->setText("Disconnected!");
    qDebug() << "Disconnected!";
    socket->close();
}

void Widget::readyRead_socket()
{
    qDebug() << "Reading...";

    //Read socket
    QString readData = socket->readAll();

    qDebug() << "Receive << " + readData;

}

void Widget::on_pushButton_Send_clicked()
{
    socket->write(ui->lineEdit->text().toLatin1().data());
}

void Widget::on_pushButton_Connect_clicked()
{
    qDebug() << "Connecting,..";
    socket->connectToHost("192.168.1.68", 1234);//"192.168.0.103" , "172.16.4.101", "10.211.55.3"
    if(!socket->waitForConnected(1000))
    {
        qDebug() << "Connect FAIL";
    }
}

void Widget::on_pushButton_Disconnect_clicked()
{
    socket->close();
}
