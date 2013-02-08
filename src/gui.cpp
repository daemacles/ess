#include "gui.h"

#include <QLabel>
#include <QFrame>
#include <QDesktopWidget>
#include <string>
#include <math.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <stdio.h>

#include "entityhandler.h"
#include "glcanvas.h"
#include "openglobject.h"
#include "keyboardinput.h"

#define ZOOM_1 50.0f

static GLuint texName;

GUI::GUI(EntityHandler* entityhandler, Simulator* sim) {
    this->entityHandler = new EntityHandler();
    this->simulator = new Simulator(this->entityHandler);
    bgSprite = Sprite::loadFromFile("stars.bmp");
    bgGroundSprite = Sprite::loadFromFile("dirt.bmp");

    planetRotation = 0.0f;
}

QWidget* GUI::setupSensors() {
    QWidget* sensorList = new QWidget;
    QVBoxLayout* sensorListLayout = new QVBoxLayout;
    sensorList->setLayout(sensorListLayout);
    sensorListLayout->addWidget(new QLabel("Sensors"));

    std::map<std::string, Sensor*> sensors = this->entityHandler->sensors;

    for(auto o : sensors) {
        Sensor* s = o.second;

        QWidget* sensorRow = new QWidget;
        QHBoxLayout* sensorRowLayout = new QHBoxLayout;
        sensorRow->setLayout(sensorRowLayout);

        /*
           std::ostringstream buff;
           buff << s->getValue();
           QLabel* sensorValueLabel = new QLabel(buff.str().c_str());

           sensorRowLayout->addWidget(sensorValueLabel);
           */
        sensorRowLayout->addWidget(new QLabel(s->getName().c_str()));

        sensorListLayout->addWidget(sensorRow);
    }

    return sensorList;

}

void GUI::setup() {

    QWidget* window = this;

    // GL screen widget
    this->glCanvas = new GLCanvas(window);
    this->glCanvas->setMinimumSize(GL_WIDTH,GL_HEIGHT);
    this->glCanvas->beginDraw();

    // Set up timer to update GL screen
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(draw()));
    timer->start(1);

    QWidget* sensorList = this->setupSensors();

    QPushButton *resetButton = new QPushButton("Reset");
    QPushButton *button3= new QPushButton("Reset");
    QPushButton *button4= new QPushButton("Reset");

    QVBoxLayout* vlayout = new QVBoxLayout;
    QWidget* buttonRow = new QWidget;

    vlayout->addWidget(this->glCanvas);
    vlayout->addWidget(buttonRow);

    QHBoxLayout* buttonRowLayout = new QHBoxLayout;

    buttonRowLayout->addWidget(sensorList);
    buttonRowLayout->addWidget(resetButton);
    buttonRowLayout->addWidget(button3);
    buttonRowLayout->addWidget(button4);
    buttonRow->setLayout(buttonRowLayout);

    window->setLayout(vlayout);
    window->show();
}

void GUI::drawBackgroundImage(Sprite* sprite, float x1, float y1, float x2, float y2, float depth, float rotation) {
    glPushMatrix();
    glLoadIdentity();

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sprite->width, 
            sprite->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
            sprite->data);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texName);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0 + rotation, 0.0); glVertex3f(x1, y1, depth);
    glTexCoord2f(0.0 + rotation, 1.0); glVertex3f(x1, y2, depth);
    glTexCoord2f(1.0 + rotation, 1.0); glVertex3f(x2, y2, depth);
    glTexCoord2f(1.0 + rotation, 0.0); glVertex3f(x2, y1, depth);

    glEnd();
    glFlush();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

void GUI::drawBackground() {
    this->drawBackgroundImage(bgSprite, -ZOOM_1, -ZOOM_1+5, ZOOM_1, ZOOM_1+5, -99.0f, planetRotation);
}

void GUI::drawGroundBackground() {
    this->drawBackgroundImage(bgGroundSprite, -ZOOM_1, -ZOOM_1+5, ZOOM_1, 0, -98.0f, 0);
}

void GUI::setupLight() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);


#define LIGHT_STRENGHT 0.3f
    GLfloat ambientLight[] = {LIGHT_STRENGHT, LIGHT_STRENGHT, LIGHT_STRENGHT, 0};
    GLfloat position[] = { 20.0f, 10.0f, 20.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void GUI::draw() {
    // This function draws all objects in the world and updates the OpenGL
    // canvas

    // Update physics
    this->simulator->stepSimulation(1./60.);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);


    // Draw space image
    this->drawBackground();
    planetRotation += -0.001f;

    // Draw moon dirt image
    //this->drawGroundBackground();

    this->setupLight();

    for(auto o : this->entityHandler->staticEnts) {
        Entity* e = o.second;
        e->getOpenGLObject()->draw(e->getPose());
    }
    for(auto o : this->entityHandler->dynamicEnts) {
        Entity* e = o.second;
        e->getOpenGLObject()->draw(e->getPose());
    }

    this->glCanvas->endDraw();

    // Render screen
    this->glCanvas->updateGL();

    // Listen for keyboard
    QCoreApplication::instance()->installEventFilter(new KeyboardInput(this->entityHandler));
}

