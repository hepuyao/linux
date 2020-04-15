#include "client.h"


/*
 *需要关注的是构造函数中的绑定dbus信号，
 * 并在槽函数中对接收到的信号进行处理。
 * 任务栏提供的点击信号是sendToUkuiDEApp，没有参数
*/
Client::Client()
{
    QDBusConnection::sessionBus().connect(QString(), QString("/taskbar/click"), "com.ukui.panel.plugins.taskbar", "sendToUkuiDEApp", this, SLOT(client_get(void)));
}

void Client::client_get()
{
    qDebug() << "Client get!";
}

/*
void client_listen()
{
    while(true)
    {
        getchar();
        qDebug() << "Message send!";
        QDBusMessage message =QDBusMessage::createSignal("/citos/path", "com.citos.test", "send_to_service");
        message << QString("Hello world!");
        QDBusConnection::sessionBus().send(message);
    }
}
*/
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Client client;
/*
    std::thread th1(client_listen);
    th1.detach();
*/
    return a.exec();
}
