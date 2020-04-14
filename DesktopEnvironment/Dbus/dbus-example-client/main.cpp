#include <QCoreApplication>
#include "dbus_demo_example_client.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	
	qRegisterMetaType<dbus_demo_example_struct>("dbus_demo_example_struct");
	qDBusRegisterMetaType<dbus_demo_example_struct>();

	dbus_demo_example_client demo;
	demo.Connect_return_integer();
//	demo.Connect_set_variantlist();
    demo.Connect_set_variantlist_2();
    demo.Connect_return_variantlist();
	return a.exec();
}
