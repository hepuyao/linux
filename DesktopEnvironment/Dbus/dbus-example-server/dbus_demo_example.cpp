#include "dbus_demo_example.h"
#include "dbus_demo_example_struct.h"
#include <stdio.h>

dbus_demo_example::dbus_demo_example()
{
	
}
void dbus_demo_example:: set_integer(int argc)
{
	printf("set_integer: %d\n", argc);	
}

void dbus_demo_example:: set_string(QString argc)
{
	printf("set_string: %s\n", argc.toStdString().data());	
}

void dbus_demo_example:: set_variantlist(int cnt, QVariantList argc)
{
	printf("set_variantlist cnt: %d\n", cnt);
}

int dbus_demo_example:: return_integer()
{
	printf("2222222222222222\n");
	int a1, a2;
	a1 = 10;
	a2 = 20;
	return a1 + a2;
}

bool dbus_demo_example:: return_bool()
{
	bool result;
	result = true;
	return result;
}

QString dbus_demo_example:: return_string()
{
	QString name = "zhangsan";
	return name;
}

QVariantList dbus_demo_example::return_variantlist()
{
	QVariantList value;
	QVariant cnt;
	struct dbus_demo_example_struct demo[3];
	for(int i = 0; i < 3; i++)
	{
		demo[i].drv_ID = 1;
		demo[i].name   = "wangwu";
		demo[i].full_name = "lisi";
		demo[i].notify_mid = 2;
		cnt = QVariant::fromValue(demo[i]);
		value << cnt;
	}
	return value;
}

int dbus_demo_example:: return_integet_and_set_integer(int argc_1, const QString &argc_2, QString &out1)
{
	int a;
	a = argc_1;
	out1 = argc_2;
	return a;
}

int dbus_demo_example:: return_integet_and_set_integet_2(int argc_1)
{
	int value;
	value = argc_1 + 1;
	return value;
}

QString dbus_demo_example:: return_string_and_set_string(const QString &argc_1)
{
	QString value;
	value = argc_1.toLower();
	return value;
}

int dbus_demo_example:: set_variantlist_2(QVariantList argc)
{
	QList<dbus_demo_example_struct*> infos;
	for (int i = 0; i < argc.size(); i++)
	{
		struct dbus_demo_example_struct *demo = new dbus_demo_example_struct;
		argc.at(i).value<QDBusArgument>() >> *demo;
		printf("drv_ID : %d\n", demo->drv_ID);
		printf("name: %s\n", demo->name.toStdString().data());
		printf("full_name : %s\n", demo->full_name.toStdString().data());
		printf("iccid : %d\n",demo->notify_mid);
	}
	printf("%d\n",argc.size());
	int cc = 1000;
	return cc;
}
