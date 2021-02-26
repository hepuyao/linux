#include "service.h"

Service::Service()
{
    QDBusConnection::sessionBus().unregisterService("org.ukui.test");
    QDBusConnection::sessionBus().registerService("org.ukui.test");
    QDBusConnection::sessionBus().registerObject("/", this,QDBusConnection :: ExportAllSlots | QDBusConnection :: ExportAllSignals);
    QTimer *mTimer=new QTimer(this);
    connect(mTimer, &QTimer::timeout, [this]{
        QDBusMessage message =QDBusMessage::createSignal("/", "org.ukui.test", "DbusSingleTest");
        message<<"dbus single test";
        QDBusConnection::sessionBus().send(message);
    });
    mTimer->start(5000);

}
void Service::service_get(QString st)
{
    qDebug() << "Message get from client: "<< st;
}

void service_listen()
{
    while(true)
    {
        getchar();
//        qDebug() << "Message send!";
        QDBusMessage message =QDBusMessage::createSignal("/taskbar/click", "com.ukui.panel.test", "sendToUkuiDEApp");
        QDBusConnection::sessionBus().send(message);
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Service service;

    std::thread th1(service_listen);
    th1.detach();

    return a.exec();
}
