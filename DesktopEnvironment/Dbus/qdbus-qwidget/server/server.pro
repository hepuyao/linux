#-------------------------------------------------
#
# Project created by QtCreator 2019-06-29T11:18:10
#
#-------------------------------------------------

QT       += core gui dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = server
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    dbus.cpp \
    dbus-adaptor.cpp

HEADERS  += widget.h \
    dbus.h \
    dbus-adaptor.h

FORMS    += widget.ui
