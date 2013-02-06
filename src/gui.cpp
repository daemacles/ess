#include "gui.h"

#include <QLabel>
#include <QFrame>
#include <QDesktopWidget>
#include <string>
#include <math.h>
#include <time.h>
#include <iostream>
#include <sstream>

#include "entityhandler.h"
#include "glcanvas.h"
#include "openglobject.h"
#include "keyboardinput.h"

float ff = 0.0;

void draw_entity_openglob(Entity* e) {
    Pose pose = e->getPose();
    //e->getOpenGLObject()->draw(sin(ff), 0, 0);
    ff += 0.05;
    //e->getOpenGLObject()->draw(pose->pos.x, pose->pos.y, pose->pos.z);
}

GUI::GUI(EntityHandler* entityhandler, Simulator* sim) {
    this->entityHandler = new EntityHandler();
    this->simulator = new Simulator(this->entityHandler);
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
    this->glCanvas->setMinimumSize(1024,480);
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

void GUI::draw() {
    this->simulator->stepSimulation(1./60.);

    //glCanvas->resize(700,500);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    //glDisable( GL_LIGHTING );                   // Turn Off Lighting
    //glCanvas->draw();
    //
    //OpenGLObject* globj = new OpenGLObject(NULL);
    //
    /*
    glColorMaterial ( GL_FRONT_AND_BACK, GL_EMISSION ) ;
   glEnable ( GL_COLOR_MATERIAL ) ;
    glEnable(GL_LIGHT1);
    */

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
    GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat position[] = { -1.5f, 1.0f, -4.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glColor3f ( 1.0f, 0.0f, 0.0f ) ;
    for(auto o : this->entityHandler->staticEnts) {
        Entity* e = o.second;
        e->getOpenGLObject()->draw(&e->getPose());
    }
    glColor3f ( 0.0f, 1.0f, 0.0f ) ;
    for(auto o : this->entityHandler->dynamicEnts) {
        Entity* e = o.second;
        e->getOpenGLObject()->draw(&e->getPose());
    }


    //draw_entity_openglob(this->entityHandler->getEntities()[0]);
    //this->entityHandler->getEntities()[0]->getOpenGLObject()->draw(0,0,0);

    //globj->draw(0,0,0);

    this->glCanvas->endDraw();

    /*
    glPushAttrib( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ENABLE_BIT | GL_POLYGON_BIT | GL_STENCIL_BUFFER_BIT );
    glDepthMask( GL_FALSE );                    // Turn Off Writing To The Depth-Buffer
    glDepthFunc( GL_LEQUAL );
    glEnable( GL_STENCIL_TEST );                    // Turn On Stencil Buffer Testing
    glColorMask( GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE );      // Don't Draw Into The Colour Buffer
    glStencilFunc( GL_ALWAYS, 1, 0xFFFFFFFFL );
    */

    this->glCanvas->updateGL();

    QCoreApplication::instance()->installEventFilter(new KeyboardInput(this->entityHandler));
}

