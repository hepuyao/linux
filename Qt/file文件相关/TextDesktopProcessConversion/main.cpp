#include "desktopprocessconversion.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DesktopProcessConversion w;
    w.show();
    return a.exec();
}
