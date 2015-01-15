#-------------------------------------------------
#
# Project created by QtCreator 2014-07-17T12:24:00
#
#-------------------------------------------------

QT       += core gui
QT       +=network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Q1_Control_Panel
TEMPLATE = app

SOURCES += main.cpp\
	mainwindow.cpp \
    cubie.cpp \
    connectdialog.cpp \
    keysdialog.cpp

HEADERS  += mainwindow.h \
    cubie.h \
    connectdialog.h \
    keysdialog.h

FORMS    += mainwindow.ui \
    connectdialog.ui \
    keysdialog.ui

RESOURCES += \
    resources.qrc

