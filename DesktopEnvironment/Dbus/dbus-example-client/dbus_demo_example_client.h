#include <QObject>
#include <QDBusInterface>
#include <QDBusPendingCallWatcher>
#include "dbus_demo_example_struct.h"
class dbus_demo_example_client : public QObject
{
	Q_OBJECT
public:
	explicit dbus_demo_example_client(QObject *parent = nullptr);
	void Connect_set_variantlist();
	void Connect_return_integer();
	void Connect_set_variantlist_2();
    void Connect_return_variantlist();

private:
	void ConnectToService();
    QList<dbus_demo_example_struct *>  value;

private slots:
    void onComplete(QDBusPendingCallWatcher *watcher);
private:
	QDBusInterface                  *serviceInterface;
};
