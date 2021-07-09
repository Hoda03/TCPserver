#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_buttonsend_clicked();

    void on_buttonclose_clicked();
    void on_send_clicked();

    void on_close_clicked();

private:
    Ui::Widget *ui;
    QTcpServer *tcpserver;
    QTcpSocket *tcpsocket ;
};
#endif // WIDGET_H
