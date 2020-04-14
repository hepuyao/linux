#include <QObject>
#include <QList>
#include"dbus_demo_example_struct.h"

class dbus_demo_example : public QObject
{
	Q_OBJECT
    //定义Interface名称
    Q_CLASSINFO("D-Bus Interface", "Dbus.Demo.Example.Interface")
public:
	explicit dbus_demo_example();

public slots:
	void set_integer(int argc);
	void set_string(QString argc);
	void set_variantlist(int cnt, QVariantList argc);
	int  set_variantlist_2(QVariantList argc);
	
	int           return_integer();
	bool          return_bool();
	QString       return_string();
	QVariantList  return_variantlist();
	int 		  return_integet_and_set_integer(int argc_1, const QString &argc_2, QString &out1);
	int 		  return_integet_and_set_integet_2(int argc_1);
	QString 	  return_string_and_set_string(const QString &argc_1);
private:
	int dbus_integer;
	QString dbus_string;
	QVariant dbus_variant;
    QList<dbus_demo_example_struct>  value;
};
