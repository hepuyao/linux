#include "testlistenscreen.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestListenScreen w;
    w.show();
    return a.exec();
}
