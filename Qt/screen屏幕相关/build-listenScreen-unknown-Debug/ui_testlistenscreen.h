/********************************************************************************
** Form generated from reading UI file 'testlistenscreen.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTLISTENSCREEN_H
#define UI_TESTLISTENSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestListenScreen
{
public:

    void setupUi(QWidget *TestListenScreen)
    {
        if (TestListenScreen->objectName().isEmpty())
            TestListenScreen->setObjectName(QString::fromUtf8("TestListenScreen"));
        TestListenScreen->resize(800, 600);

        retranslateUi(TestListenScreen);

        QMetaObject::connectSlotsByName(TestListenScreen);
    } // setupUi

    void retranslateUi(QWidget *TestListenScreen)
    {
        TestListenScreen->setWindowTitle(QApplication::translate("TestListenScreen", "TestListenScreen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TestListenScreen: public Ui_TestListenScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTLISTENSCREEN_H
