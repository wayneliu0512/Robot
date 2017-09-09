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

    socket->connectToHost("192.168.1.68", 1234);//"192.168.0.103" , "172.16.4.101", "10.211.55.3"
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
    QString str = "ccd";
    socket->write(str.toLatin1());
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
    QByteArray readData = socket->readAll();

    //Tranfer socket to Json Format , get ID and CMD
    QJsonDocument doc = QJsonDocument::fromJson(readData);
    QJsonValue cmd_value = doc.object().value("CMD");
    ID_value = doc.object().value("ID");

    qDebug() << "CmdValue: " + cmd_value.toString();

    //If Command is Shot , then take a shot
    if(cmd_value.toString() == "Shot")
    {
        //Create Json Format data to do ACK respond
        QJsonObject ccd_Obj_ACK;
        ccd_Obj_ACK.insert("ID", ID_value);
        ccd_Obj_ACK.insert("Type", "ACK");
        QJsonDocument doc(ccd_Obj_ACK);
        QByteArray sendData = doc.toJson();

        //Do ACK respond
        socket->write(sendData);

        qDebug() << " SendData: " + sendData;

        //Take a shot here...

        //Wait for 2 Second to simulate Taking a shot
        //After taking a shot , do DONE respond
        QTimer::singleShot(2000, this, &Widget::DONE_Respond);
    }
}

//Create Json Format data to do DONE respond
void Widget::DONE_Respond()
{
    //Create Json Format data to do DONE respond
    QJsonObject ccd_Obj_DONE;
    ccd_Obj_DONE.insert("ID", ID_value);
    ccd_Obj_DONE.insert("Type", "DONE");
    ccd_Obj_DONE.insert("SN", ui->lineEdit->text());
    ccd_Obj_DONE.insert("MAC", ui->lineEdit_2->text());
    QJsonDocument doc(ccd_Obj_DONE);
    QByteArray sendData = doc.toJson();

    //Do ACK respond
    socket->write(sendData);

    qDebug() << " SendData: " + sendData;
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
