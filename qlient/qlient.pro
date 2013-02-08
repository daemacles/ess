#-------------------------------------------------
#
# Project created by QtCreator 2013-02-07T23:34:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = qlient
TEMPLATE = app

SOURCES += main.cpp\
        qtessclient.cpp

HEADERS  += qtessclient.h

FORMS    += qtessclient.ui

INCLUDEPATH += $$PWD/../src

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += libzmq jsoncpp

unix:!macx:!symbian: PRE_TARGETDEPS += $$PWD/../src/libessclient.a

unix:!macx:!symbian: LIBS += -lpthread -L$$PWD/../src/ -lessclient
