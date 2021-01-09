#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QLabel>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QDebug>
#include <QProcess>
#include <QDBusMessage>
#include <QDBusConnection>
#include <QRegExp>
#include <QEvent>
class Widget : public QMainWindow
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.ukui.backup.plugins")

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void widgetprocess();

private slots:
    void finished(int exitCode,QProcess::ExitStatus exitStatus);
};
#endif // WIDGET_H
