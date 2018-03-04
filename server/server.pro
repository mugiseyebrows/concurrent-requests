#-------------------------------------------------
#
# Project created by QtCreator 2018-03-04T19:39:28
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    worker.cpp \
    thread.cpp

HEADERS  += mainwindow.h \
    worker.h \
    thread.h

FORMS    += mainwindow.ui
