TEMPLATE = app
TARGET = phys_demo
QT += opengl
QMAKE_CXX = g++-4.7
DEPENDPATH += . ../esscommon 
INCLUDEPATH += . ../esscommon
QMAKE_CXXFLAGS += -std=c++11 -g
CONFIG += link_pkgconfig
PKGCONFIG += libzmq jsoncpp bullet
LIBS += -L. -L../esscommon -lesscommon -lOpenGLSupport -lGL -lGLU -glut -lm

SOURCES += CcdPhysicsDemo.cpp \
           phys_main.cpp

HEADERS += CcdPhysicsDemo.h \
           GLDebugFont.h \
           GL_Simplex1to4.h \
           Win32DemoApplication.h \
           DebugCastResult.h \
           GL_DialogDynamicsWorld.h \
           GlutDemoApplication.h \
           DemoApplication.h \
           GL_DialogWindow.h \
           GlutStuff.h \
           GLDebugDrawer.h \
           GL_ShapeDrawer.h \
           RenderTexture.h
