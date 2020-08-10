#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileSystemWatcher>
#include <QDir>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QFileSystemWatcher *fsWatcher;
};

#endif // WIDGET_H
