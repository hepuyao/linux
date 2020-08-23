#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileSystemWatcher>
#include <QDir>
#include <QMap>

//namespace Ui {
//class Widget;
//}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
//    Ui::Widget *ui;
    QFileSystemWatcher *fsWatcher;
    QMap<QString, QStringList> m_currentContentsMap; // 当前每个监控的内容目录列表
    void directoryUpdated(const QString &path);
};

#endif // WIDGET_H
