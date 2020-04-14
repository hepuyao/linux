#include <QtDBus/QDBusConnection>
#include <QCoreApplication>
#include <QDebug>
#include <QDBusError>
#include <QDBusMetaType>
#include "dbus_demo_example.h"
#include "dbus_demo_example_struct.h"
#include "example_adaptor.h"
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	qRegisterMetaType<dbus_demo_example_struct>("dbus_demo_example_struct");
	qDBusRegisterMetaType<dbus_demo_example_struct>();
	QDBusConnection connection = QDBusConnection::systemBus();

	if (!connection.registerService("dbus.demo.example")) {
		qDebug() << "error:" << connection.lastError().message();
		exit(-1);
	}
	
	dbus_demo_example *dbus_demo = new dbus_demo_example();
	new IterfaceAdaptor(dbus_demo);
	connection.registerObject("/dbus/demo/example", dbus_demo);
	
	return a.exec();	
}
