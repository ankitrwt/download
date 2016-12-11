#-------------------------------------------------
#
# Project created by QtCreator 2016-12-07T21:35:30
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = download
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp downloadmanager.cpp textprogressbar.cpp

HEADERS  += dialog.h downloadmanager.h textprogressbar.h

FORMS    += dialog.ui
