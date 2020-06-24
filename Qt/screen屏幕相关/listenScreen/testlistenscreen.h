#ifndef TESTLISTENSCREEN_H
#define TESTLISTENSCREEN_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class TestListenScreen; }
QT_END_NAMESPACE

class TestListenScreen : public QWidget
{
    Q_OBJECT

public:
    TestListenScreen(QWidget *parent = nullptr);
    ~TestListenScreen();

private:
    Ui::TestListenScreen *ui;

private slots:
    void onScreenChanged(QScreen *);
};
#endif // TESTLISTENSCREEN_H
