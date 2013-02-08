TEMPLATE = lib

DEPENDPATH += . ../esscommon
INCLUDEPATH += . ../esscommon
QMAKE_CXXFLAGS += -std=c++11 -g 
CONFIG += link_pkgconfig
PKGCONFIG += libzmq jsoncpp
LIBS += -L../esscommon -lesscommon -lm

SOURCES = essclient.cpp
HEADERS = essclient.h

