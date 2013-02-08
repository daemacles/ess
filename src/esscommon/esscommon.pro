TEMPLATE = lib

isEmpty(PREFIX) {
 PREFIX=/usr/local/lib
}
TARGET.path = $$PREFIX/

QMAKE_CXX = g++-4.7

QT += opengl
DEPENDPATH += .
INCLUDEPATH += .
QMAKE_CXXFLAGS += -std=c++11 -g 
CONFIG += link_pkgconfig
PKGCONFIG += bullet libzmq jsoncpp
LIBS += -L. -lm

SOURCES = \
          entity.cpp \
          entityhandler.cpp \
          ground.cpp \
          gyrosensor.cpp \
          jsonserializer.cpp \
          objparser.cpp \
          openglobject.cpp \
          platform.cpp \
          pose.cpp \
          rocket.cpp \
          sensor.cpp \
          shapehandler.cpp \
          simulator.cpp \
          sprite.cpp \
          stlmesh.cpp \
          zmqhandler.cpp

HEADERS = \
          accelsensor.h \
          distancesensor.h \
          entity.h \
          entityhandler.h \
          ground.h \
          gyrosensor.h \
          jsonserializer.h \
          networkhandler.h \
          objparser.h \
          openglobject.h \
          physobject.h \
          platform.h \
          pose.h \
          radar.h \
          rocketcontrol.h \
          rocket.h \
          sensor.h \
          sensormessage.h \
          shapehandler.h \
          simulator.h \
          sprite.h \
          stb_image.h \
          stlmesh.h \
          util.h \
          zmqhandler.h

