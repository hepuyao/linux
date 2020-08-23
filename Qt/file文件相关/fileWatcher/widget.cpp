#include "widget.h"
//#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent)
    //ui(new Ui::Widget)
{
    //ui->setupUi(this);
    fsWatcher=new QFileSystemWatcher(this);

    QString all_conf_path ="/usr/share/applications/";
    QString android_path =QDir::homePath()+"/.local/share/applications/";

    fsWatcher->addPath(all_conf_path);
    fsWatcher->addPath(android_path);

    connect(fsWatcher,&QFileSystemWatcher::directoryChanged,[this](){
               directoryUpdated(all_conf_path);
               directoryUpdated(android_path);
            });
}

Widget::~Widget()
{
//    delete ui;
}

// 只要任何监控的目录更新（添加、删除、重命名），就会调用。
void Widget::directoryUpdated(const QString &path)
{
    // 比较最新的内容和保存的内容找出区别(变化)
    QStringList currEntryList = m_currentContentsMap[path];
    const QDir dir(path);
    QStringList newEntryList = dir.entryList(QDir::NoDotAndDotDot  | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
    QSet<QString> newDirSet = QSet<QString>::fromList(newEntryList);
    QSet<QString> currentDirSet = QSet<QString>::fromList(currEntryList);

    // 添加了文件
    QSet<QString> newFiles = newDirSet - currentDirSet;
    QStringList newFile = newFiles.toList();

    // 文件已被移除
    QSet<QString> deletedFiles = currentDirSet - newDirSet;
    QStringList deleteFile = deletedFiles.toList();

    // 更新当前设置
    m_currentContentsMap[path] = newEntryList;

    if (!newFile.isEmpty() && !deleteFile.isEmpty())
    {
        // 文件/目录重命名
        if ((newFile.count() == 1) && (deleteFile.count() == 1))
        {
//            qDebug() << QString("File Renamed from %1 to %2").arg(deleteFile.first()).arg(newFile.first());
        }
    }
    else
    {
        // 添加新文件/目录至Dir
        if (!newFile.isEmpty())
        {
            foreach (QString file, newFile)
            {
                // 处理操作每个新文件....
            }
        }
        // 从Dir中删除文件/目录
        if (!deleteFile.isEmpty())
        {
            foreach(QString file, deleteFile)
            {
                // 处理操作每个被删除的文件....

                qDebug()<<path+file;
            }
        }
    }
}
