#include "testlistenscreen.h"
#include "ui_testlistenscreen.h"
#include <QDebug>
#include <QScreen>

TestListenScreen::TestListenScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TestListenScreen)
{
    ui->setupUi(this);
    QGuiApplication* guiApp = dynamic_cast<QGuiApplication*>(qApp);
    qDebug()<<"********99999999999****";
    connect(qApp,SIGNAL(primaryScreenChanged(QScreen *)),this,SLOT(onScreenChanged(QScreen *)));
}

TestListenScreen::~TestListenScreen()
{
    delete ui;
}

void TestListenScreen::onScreenChanged(QScreen *s)
{
    qDebug()<<"************************";
}
