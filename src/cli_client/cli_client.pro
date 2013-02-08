TEMPLATE = app
TARGET = cli_client
QMAKE_CXX = g++-4.7
DEPENDPATH += . ../esscommon ../libessclient
INCLUDEPATH += . ../esscommon ../libessclient
QMAKE_CXXFLAGS += -std=c++11 -g
CONFIG += link_pkgconfig
PKGCONFIG += libzmq jsoncpp
LIBS += -L../libessclient -lessclient -lm

SOURCES += cli_client.cpp
