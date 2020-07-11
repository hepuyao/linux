#include <QtCore/QCoreApplication>
#include "filesystemwatcher.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    FileSystemWatcher::addWatchPath("/home/kylin/");
    return a.exec();
}
