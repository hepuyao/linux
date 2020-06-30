#include "turnpage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TurnPage w;
    w.show();
    return a.exec();
}
