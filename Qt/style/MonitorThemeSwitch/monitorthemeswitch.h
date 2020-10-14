#ifndef MONITORTHEMESWITCH_H
#define MONITORTHEMESWITCH_H

#include <QWidget>
#include <QGSettings/QGSettings>

QT_BEGIN_NAMESPACE
namespace Ui { class MonitorThemeSwitch; }
QT_END_NAMESPACE

class MonitorThemeSwitch : public QWidget
{
    Q_OBJECT

public:
    MonitorThemeSwitch(QWidget *parent = nullptr);
    ~MonitorThemeSwitch();

private:
    Ui::MonitorThemeSwitch *ui;
    QGSettings *style_settings;
};
#endif // MONITORTHEMESWITCH_H
