#include "widget.h"
#include "ui_widget.h"
#include <QDBusInterface>
#include <QDBusReply>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("客户端");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QDBusInterface iface("com.kylin.security.controller.filectrl",
                         "/",
                         "com.kylin.security.controller.filectrl",
                         QDBusConnection::sessionBus());
    QDBusReply<bool> reply=iface.call("RemoveFromTaskbar","123");
    qDebug()<<reply;
}
