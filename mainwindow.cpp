#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPluginLoader>
#include <QMessageBox>
#include <QDir>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(!loadPlugin())
    {
        //如果无法加载插件
        QMessageBox::information(this,"Error","Could not load the plugin");
        ui->lineEdit->setEnabled(false);
        ui->pushButton->setEnabled(false);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
bool MainWindow::loadPlugin()
{
    QDir pluginsDir("/home/hepuyao/2019/8/1.资料/1.插件机制/1.插件003 实现插件数字的相加/build-plugin3-unknown_176419-Release");
    //QDir pluginsDir("/home/kylin/temp5");
    //QDir pluginsDir("/home/kylin/temp/build-plugin-Imported_Kit-Release");
/*
    //遍历插件目录
    QMessageBox::information(this,"Error","111111111111111111111111");
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
         QMessageBox::information(this,"Error","2222222222222222222222222");
        qDebug()<<fileName;
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
         QMessageBox::information(this,"Error","33333333333333");
        if(plugin)
        {
            qDebug()<<"instance plugin";
             QMessageBox::information(this,"Error","44444444444444444444444");
            regExpInterface = qobject_cast<RegExpInterface*>(plugin);
             QMessageBox::information(this,"Error","666666666666666666666666");
            if(regExpInterface)
            {
                qDebug()<<"fint the plugin";
                 QMessageBox::information(this,"Error","555555555555555555555555555");
                return true;
            }
        }
        qDebug()<<"isn't the plugin";
    }
    return false;
}
*/
    //遍历插件目录
    //QMessageBox::information(this,"Error","111111111111111111111111");
    foreach (QString fileName, pluginsDir.entryList(QDir::Files))
    {
         //QMessageBox::information(this,"Error","2222222222222222222222222");
        qDebug()<<fileName;
        QMessageBox::information(this,"Error",fileName);

        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
         //QMessageBox::information(this,"Error","3333333333333333333");
        if(plugin)
        {
            qDebug()<<"instance plugin";

             //QMessageBox::information(this,"Error","44444444444444444444444");
            regExpInterface = qobject_cast<RegExpInterface*>(plugin);//**************
             //QMessageBox::information(this,"Error","666666666666666666666666");
            if(regExpInterface)
            {
                QMessageBox::information(this,"Error","7");

                qDebug()<<"fint the plugin";
                 //QMessageBox::information(this,"Error","555555555555555555555555555");
                return true;
            }
        }
        qDebug()<<"isn't the plugin";
    }
    return false;
}

//rewrite plugin
//void MainWindow::on_pushButton_clicked()
//{
//    //QString str=QString::number(c,10);
//    //QString  str = regExpInterface->add_num(ui->lineEdit->text());
//    QString str = regExpInterface->add_num(ui->lineEdit->text());
//    ui->label->setText(str);
//    //QString str = regExpInterface->regexp(ui->lineEdit->text());
    
   
    
    
//}

