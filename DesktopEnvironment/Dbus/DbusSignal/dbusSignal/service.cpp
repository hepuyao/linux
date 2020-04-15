#include "service.h"

Service::Service()
{
    QDBusConnection::sessionBus().unregisterService("com.ukui.panel.plugins.service");
    QDBusConnection::sessionBus().registerService("com.ukui.panel.plugins.service");
    QDBusConnection::sessionBus().registerObject("/taskbar/click", this,QDBusConnection :: ExportAllSlots | QDBusConnection :: ExportAllSignals);
//    QDBusConnection::sessionBus().connect(QString(), QString("/taskbar/click"), "com.ukui.panel.plugins.taskbar", "sendToUkuiDEApp", this, SLOT(service_get(QString)));
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
        QDBusMessage message =QDBusMessage::createSignal("/taskbar/click", "com.ukui.panel.plugins.taskbar", "sendToUkuiDEApp");
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
