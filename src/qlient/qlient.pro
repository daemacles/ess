#-------------------------------------------------
#
# Project created by QtCreator 2013-02-07T23:34:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11 -g

TARGET = qlient
TEMPLATE = app

SOURCES += main.cpp\
        qtessclient.cpp \

HEADERS  += qtessclient.h \

FORMS    += qtessclient.ui

INCLUDEPATH += $$PWD/../src
DEPENDPATH += . ../esscommon ../essclient
INCLUDEPATH += . ../esscommon ../essclient
CONFIG += link_pkgconfig
PKGCONFIG += libzmq jsoncpp
LIBS += -L../essclient -lessclient -lm

