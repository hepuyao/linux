#include "monitorthemeswitch.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MonitorThemeSwitch w;
    w.show();
    return a.exec();
}
