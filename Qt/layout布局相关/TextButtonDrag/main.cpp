#include "dragwidget.h"
#include <QApplication>
#include <QIcon>
#include <QPixmap>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DragWidget ww;
    ww.setGeometry(200,200,800,200);

    DragButton w(&ww);
    w.setPixmap("/usr/share/ukui-panel/plugin-startmenu/img/startmenu.svg");
    w.setText("按钮1");
    w.setInitialScaling(0.6);

    DragButton w2(&ww);
    w2.setPixmap("/usr/share/ukui-panel/plugin-startmenu/img/startmenu.svg");
    w2.setText("按钮2");
    w2.setInitialScaling(0.6);

    DragButton w3(&ww);
    w3.setPixmap("/usr/share/ukui-panel/plugin-startmenu/img/startmenu.svg");
    w3.setText("按钮3");
    w3.setInitialScaling(0.6);

    DragButton w4(&ww);
    w4.setPixmap("/usr/share/ukui-panel/plugin-startmenu/img/startmenu.svg");
    w4.setText("按钮4");
    w4.setInitialScaling(0.6);

    ww.addButton(&w);
    ww.addButton(&w2);
    ww.addButton(&w3);
    ww.addButton(&w4);
    ww.show();

    return a.exec();
}
