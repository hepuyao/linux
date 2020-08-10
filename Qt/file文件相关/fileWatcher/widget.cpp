#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    fsWatcher=new QFileSystemWatcher(this);

    QString all_conf_path ="/home/liyanda/";

    fsWatcher->addPath(all_conf_path);

    connect(fsWatcher,&QFileSystemWatcher::directoryChanged,[this](){
               qDebug()<<"**************";
            });
}

Widget::~Widget()
{
    delete ui;
}
