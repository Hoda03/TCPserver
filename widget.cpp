#include "widget.h"
#include "ui_widget.h"
#include <QTcpSocket>
#include <QTcpServer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    tcpserver = NULL;
    tcpsocket = NULL;

    tcpserver = new QTcpServer(this);

    tcpserver -> listen(QHostAddress::Any,8888);

    connect(tcpserver, &QTcpServer::newConnection, [=](){

        tcpsocket =tcpserver -> nextPendingConnection();

        QString ip = tcpsocket -> peerAddress().toString();
        qint16 port = tcpsocket ->peerPort();

        QString temp = QString ("[%1:%2]:Server").arg(ip).arg(port);
        ui->textEdit->setText(temp);

        connect(tcpsocket,&QTcpSocket::readyRead,[=](){
            QByteArray array = tcpsocket -> readAll();
            ui-> textEdit -> append(array);
        });


    });


}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_send_clicked()
{
    if(tcpsocket == NULL)
        return;
    QString str = ui -> textEditwrite -> toPlainText();

    tcpsocket -> write(str.toUtf8().data());
}


void Widget::on_close_clicked()
{
    if(tcpsocket == NULL)
        return;
    tcpsocket -> disconnectFromHost();
    tcpsocket -> close();
    tcpsocket = NULL;

}

