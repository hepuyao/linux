#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    settings = new QGSettings("org.ukui.panel.settings");
    qDebug()<<"panelsize  :"<<settings->get("panelsize");
    connect(settings, &QGSettings::changed, this, [=] (const QString &key){
        if(key == "panelsize")
            qDebug()<<"settings   **** ";
    });


}

Widget::~Widget()
{
    delete ui;
}

