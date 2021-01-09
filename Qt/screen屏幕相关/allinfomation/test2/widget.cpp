#include "widget.h"
#include <QProcess>

#include <iostream>
#include <vector>
#include <iterator>
#include <regex>
#include <QApplication>
#include <QDesktopWidget>
#include <QRegExp>

Widget::Widget(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *verticalLayoutWidget;
    verticalLayoutWidget=new QWidget(this);
//    verticalLayoutWidget->setGeometry(0,LEAVE_BLANK_HIGHT+label_logo->height(),ABOUT_WIDGET_WIDTH,200);
//    verticalLayoutWidget->setFixedSize(500,200);
    QVBoxLayout *verticalLayout;
    verticalLayout = new QVBoxLayout(verticalLayoutWidget);

    QLabel *label1=new QLabel(this);
    label1->setText("1$$$$$$$$$$$$1$$$$$$$$$$44444444444444444444444444\
                    444444444444444444444455555\
                    5555555555555555544446666666\
                    666666666666444444444444444444444444");
                    label1->setWordWrap(true);
    QLabel *label2=new QLabel(this);
    label2->setText("1$$$$$$$$$$$$1$$$$$$$$$$44444444444444444444444444\
                    444444444444444444444455555\
                    5555555555555555544446666666\
                    666666666666444444444444444444444444");
                    label2->setWordWrap(true);
    QLabel *label3=new QLabel(this);
    label3->setText("1$$$$$$$$$$$$1$$$$$$$$$$44444444444444444444444444\
                    444444444444444444444455555\
                    5555555555555555544446666666\
                    666666666666444444444444444444444444");
                    label3->setWordWrap(true);
    QLabel *label4=new QLabel(this);
    label4->setText("4$$$$$$$$$$$$1$$$$$$$$$$44444444444444444444444444\
                    444444444444444444444455555\
                    5555555555555555544446666666\
                    666666666666444444444444444444444444");
                    label4->setWordWrap(true);
    QLabel *label5=new QLabel(this);
    label5->setText("5$$$$$$$$$$$$1$$$$$$$$$$44444444444444444444444444\
                    444444444444444444444455555\
                    5555555555555555544446666666\
                    666666666666444444444444444444444444");
                    label5->setWordWrap(true);
    QLabel *label6=new QLabel(this);
    label6->setText("6^$$$$$$$$$$$$1$$$$$$$$$$44444444444444444444444444\
                    444444444444444444444455555\
                    5555555555555555544446666666\
                    666666666666444444444444444444444444");
    label6->setWordWrap(true);
    QLabel *label7=new QLabel(this);
    label7->setText("7");

//    verticalLayout->addWidget(label_title);
//    verticalLayout->addWidget(label_info);
//    verticalLayout->addWidget(label_copyright);
//    verticalLayout->addWidget(label_website);
    verticalLayout->addWidget(label1);
    verticalLayout->addWidget(label2);
    verticalLayout->addWidget(label3);
    verticalLayout->addWidget(label4);
    verticalLayout->addWidget(label5);
    verticalLayout->addWidget(label6);
    verticalLayout->addWidget(label7);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(verticalLayoutWidget);
//    scrollArea->widget()->setLayout(verticalLayout);
    scrollArea->setFixedWidth(400);
    scrollArea->setMinimumHeight(100);
    scrollArea->move(100,100+10);


    widgetprocess();
    QDBusConnection::sessionBus().unregisterService("com.ukui.backup.plugins");
    QDBusConnection::sessionBus().registerService("com.ukui.backup.plugins");
    QDBusConnection::sessionBus().registerObject("/", this,QDBusConnection :: ExportAllSlots | QDBusConnection :: ExportAllSignals);

    QString date="/usr/share/applications/firefox.desktop";
      QStringList list = date.split("/");//QString字符串分割函数
    qDebug()<<"111"<<QString(list.at(4)).remove(".desktop") ;

    QDesktopWidget* desktopWidget = QApplication::desktop();
        //获取设备屏幕大小
        QRect screenRect = desktopWidget->screenGeometry(0);
        double screenX = screenRect.width();
        double screenY = screenRect.height();

        qDebug()<<"desktopWidget   "<<screenX<<screenY;
        //获取可用桌面大小
        QRect deskRect = desktopWidget->availableGeometry(0);
        double availableScreenX = deskRect.width();
        double availableScreenY = deskRect.height();
        qDebug()<<"availableScreen   "<<availableScreenX<<availableScreenY;
        qDebug()<<""<<deskRect.top();

        if(screenX==availableScreenX && deskRect.top()==0){qDebug()<<"bottom";}
        else if(screenX==availableScreenX && deskRect.top()!=0 ){qDebug()<<"top";}
        else if(screenY==availableScreenY && deskRect.top()==0) {qDebug()<<"left";}
        else {qDebug()<<"right";}

        qDebug()<<desktopWidget->screenCount();
        qDebug()<<"primaryScreen  is "<<desktopWidget->primaryScreen();
}

Widget::~Widget()
{
}

void Widget::widgetprocess()
{
    QProcess *process = new QProcess();
    qDebug()<<"widgetprocess    88448";

//    process->start(QString("firefox"));
    connect(process,SIGNAL(finished(int,QProcess::ExitStatus)),SLOT(finished(int,QProcess::ExitStatus)));

//    connect(process,SIGNAL(started()),SLOT(started()));

//    connect(process,SIGNAL(finished(int,QProcess::ExitStatus)),SLOT(finished()));

//    connect(process,SIGNAL(stateChanged(QProcess::ProcessState)),SLOT(stateChanged()));
}

void Widget::finished(int exitCode,QProcess::ExitStatus exitStatus)
{
    qDebug()<<"finish    888"<<exitCode;
    /*创建QT的DBus信号*/
    QDBusMessage message =QDBusMessage::createSignal("/", "com.ukui.backup.plugins", "sendToUkuiDEApp");
    QDBusConnection::sessionBus().send(message);
}
