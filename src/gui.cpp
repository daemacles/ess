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
#include "sprite.h"

#define checkImageWidth 1024
#define checkImageHeight 640

float ff = 0.0;

static GLubyte checkImage[checkImageHeight][checkImageWidth][4];
static GLuint texName;

Sprite* sprite;


void draw_entity_openglob(Entity* e) {
    Pose pose = e->getPose();
    ff += 0.05;
}

GUI::GUI(EntityHandler* entityhandler, Simulator* sim) {
    this->entityHandler = new EntityHandler();
    this->simulator = new Simulator(this->entityHandler);
    sprite = Sprite::loadFromFile("stars.bmp");

}

QWidget* GUI::setupSensors() {
    /*
    QWidget* sensorList = new QWidget;
    QVBoxLayout* sensorListLayout = new QVBoxLayout;
    sensorList->setLayout(sensorListLayout);
    sensorListLayout->addWidget(new QLabel("Sensors"));

    std::map<std::string, Sensor*> sensors;

    for(auto o : sensors) {
        Sensor* s = o.second;

        QWidget* sensorRow = new QWidget;
        QHBoxLayout* sensorRowLayout = new QHBoxLayout;
        sensorRow->setLayout(sensorRowLayout);

        std::ostringstream buff;
        buff << s->getValue();
        QLabel* sensorValueLabel = new QLabel(buff.str().c_str());

        sensorRowLayout->addWidget(new QLabel(s->getName().c_str()));
        sensorRowLayout->addWidget(sensorValueLabel);

        sensorListLayout->addWidget(sensorRow);
    }

    std::vector<Sensor*> sim_sensors = this->simulator->getSensors();

    for(std::vector<Sensor*>::iterator it = sim_sensors.begin(); it != sim_sensors.end(); ++it) {
        Sensor* s = *it;

    }
    return sensorList;
    */

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

    //QWidget* sensorList = this->setupSensors();

    QPushButton *resetButton = new QPushButton("Reset");
    QPushButton *button3= new QPushButton("Reset");
    QPushButton *button4= new QPushButton("Reset");

    QVBoxLayout* vlayout = new QVBoxLayout;
    QWidget* buttonRow = new QWidget;

    vlayout->addWidget(this->glCanvas);
    vlayout->addWidget(buttonRow);

    QHBoxLayout* buttonRowLayout = new QHBoxLayout;

    //buttonRowLayout->addWidget(sensorList);
    buttonRowLayout->addWidget(resetButton);
    buttonRowLayout->addWidget(button3);
    buttonRowLayout->addWidget(button4);
    buttonRow->setLayout(buttonRowLayout);

    window->setLayout(vlayout);
    window->show();
}

void GUI::drawBackground() {
    glPushMatrix();
    glLoadIdentity();

   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glGenTextures(1, &texName);
   glBindTexture(GL_TEXTURE_2D, texName);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                   GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sprite->width, 
                sprite->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
                sprite->data);
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
   glBindTexture(GL_TEXTURE_2D, texName);
   glBegin(GL_QUADS);
#define ZOOM_1 30.0
   glTexCoord2f(0.0, 0.0); glVertex3f(-ZOOM_1, -ZOOM_1, -99);
   glTexCoord2f(0.0, 1.0); glVertex3f(-ZOOM_1, ZOOM_1, -99);
   glTexCoord2f(1.0, 1.0); glVertex3f(ZOOM_1, ZOOM_1, -99);
   glTexCoord2f(1.0, 0.0); glVertex3f(ZOOM_1, -ZOOM_1, -99);

   glEnd();
   glFlush();
   glDisable(GL_TEXTURE_2D);

   glPopMatrix();
}

void GUI::setupLight() {
    glColorMaterial ( GL_FRONT_AND_BACK, GL_EMISSION ) ;

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat ambientLight[] = { 0.2f, 0.4, 0.4f, 1.0f };
    GLfloat position[] = { 0.5f, 0.5f, -0.5f, 0.5f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void GUI::draw() {
    this->simulator->stepSimulation(1./60.);
    //glCanvas->resize(700,500);
    glClearColor(0.0, 0.0, 0.0, 1.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);

    //glDisable( GL_LIGHTING );                   // Turn Off Lighting
    //glCanvas->draw();
    //
    //OpenGLObject* globj = new OpenGLObject(NULL);
    //
    /*
    glEnable(GL_LIGHT1);
    */

   this->drawBackground();

   this->setupLight();
    /*
    */

    for(auto o : this->entityHandler->staticEnts) {
        Entity* e = o.second;
        e->getOpenGLObject()->draw(e->getPose());
    }
    glDisable(GL_LIGHTING);
    for(auto o : this->entityHandler->dynamicEnts) {
        Entity* e = o.second;
        e->getOpenGLObject()->draw(e->getPose());
    }

    this->glCanvas->endDraw();

    this->glCanvas->updateGL();

    QCoreApplication::instance()->installEventFilter(new KeyboardInput(this->entityHandler));
}

