#include "dbus_demo_example_client.h"
#include <QDBusInterface>

dbus_demo_example_client::dbus_demo_example_client(QObject *parent)
{
	ConnectToService();
}

void dbus_demo_example_client::ConnectToService()
{
	serviceInterface = new QDBusInterface("dbus.demo.example",
			"/dbus/demo/example",
			"Dbus.Demo.Example.Interface",
			QDBusConnection::sessionBus());
	serviceInterface->setTimeout(2147483647);
}

void dbus_demo_example_client::Connect_set_variantlist()
{
	QList<QVariant> args_1;
	QList<QVariant> args_2;
	QVariant tmp;
	struct dbus_demo_example_struct data[3];
	for(int i = 0; i < 3; i++)
	{
		data[i].ID = 10;
		data[i].name = "zhangshan";
		data[i].full_name = "wangwu";
		data[i].Iccid = 1234;
		tmp = QVariant::fromValue(data[i]);
		args_1 << tmp;
	}
	args_2 << QVariant(10) << args_1;
	QDBusPendingCall call = serviceInterface->asyncCallWithArgumentList("set_variantlist", args_2);
//	QDBusMessage msg = serviceInterface->callWithArgumentList(QDBus::method,"set_variantlist", args_2);
/*	if (msg.type() == QDBusMessage::ErrorMessage) {
		printf("错误\n");
		return;
	} */
	printf("success\n");
	return ;
}

void dbus_demo_example_client::Connect_return_integer()
{
	QDBusMessage msg = serviceInterface->call("return_integer");
	if(msg.type() == QDBusMessage::ErrorMessage){
		printf("错误\n");
		return;
	}

	int value =  msg.arguments().at(0).toInt();
	printf("return_integer : %d\n", value);
	return ;

}

void dbus_demo_example_client::Connect_set_variantlist_2()
{
    QVariantList  value;
    QList<QVariant> args_1;
    QVariant tmp;
	struct dbus_demo_example_struct data[3];

	for (int i = 0; i < 3; i++) {
		data[i].ID = 10;
		data[i].name = "zhangshan";
		data[i].full_name = "wangwu";
		data[i].Iccid = 1234;
        tmp = QVariant::fromValue(data[i]);
        value << tmp;
	}
    args_1 << QVariant::fromValue(value);
	printf("%d\n", args_1.size());
    QDBusPendingCall call = serviceInterface->asyncCallWithArgumentList(QStringLiteral("set_variantlist_2"), args_1);
	QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(call, this);
	connect(watcher, &QDBusPendingCallWatcher::finished, this, &dbus_demo_example_client::onComplete);
}

void dbus_demo_example_client::onComplete(QDBusPendingCallWatcher *watcher)
{
    QDBusPendingReply<qint32> reply = *watcher;
    if(reply.isError()){
        printf("数据返回失败\n");
        return;
    }
    qint32 result = reply.argumentAt(0).toInt();
    printf("chenggong : %d\n", result);
}

void dbus_demo_example_client::Connect_return_variantlist()
{
    QDBusMessage msg = serviceInterface->call("return_variantlist");
    if(msg.type() == QDBusMessage::ErrorMessage) {
        printf("失败\n");
        return;
    }
    QDBusArgument argument = msg.arguments().at(0).value<QDBusArgument>();
    QList<QVariant> infos;
    argument >> infos;
    printf("infos:%d\n", infos.size());
    for (auto info : value)
    {
        delete info;
    }
    value.clear();
    for (int i = 0; i < infos.size(); i++)
    {
        dbus_demo_example_struct *dbus_struct = new dbus_demo_example_struct;
        infos.at(i).value<QDBusArgument>() >> *dbus_struct;
        value.push_back(dbus_struct);
    }
    for (auto info : value)
    {
        printf("ID:%d name: %s full_name: %s iccid: %d\n", info->ID, info->name.toStdString().data(), info->full_name.toStdString().data(), info->Iccid);
    }
}

