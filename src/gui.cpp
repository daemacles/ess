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

#define checkImageWidth 1024
#define checkImageHeight 640

float ff = 0.0;

static GLubyte checkImage[checkImageHeight][checkImageWidth][4];
static GLuint texName;

void makeCheckImage(void)
{
    FILE* bmp = fopen("stars.bmp", "r");
    char buf[4];
    fseek(bmp, 14, SEEK_SET);

   for (int i = 0; i < checkImageHeight; i++) {
      for (int j = 0; j < checkImageWidth; j++) {
            fread(buf, 1, 3, bmp);
         checkImage[i][j][0] = (GLubyte) buf[0];
         checkImage[i][j][1] = (GLubyte) buf[1];
         checkImage[i][j][2] = (GLubyte) buf[2];
         checkImage[i][j][3] = (GLubyte) 255;
      }
   }
    fclose(bmp);
}

void draw_entity_openglob(Entity* e) {
    Pose pose = e->getPose();
    ff += 0.05;
}

GUI::GUI(EntityHandler* entityhandler, Simulator* sim) {
    this->entityHandler = new EntityHandler();
    this->simulator = new Simulator(this->entityHandler);
    makeCheckImage();

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

void GUI::drawBackground() {
    glPushMatrix();
    glLoadIdentity();

   makeCheckImage();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glGenTextures(1, &texName);
   glBindTexture(GL_TEXTURE_2D, texName);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                   GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, 
                checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
                checkImage);
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
   glBindTexture(GL_TEXTURE_2D, texName);
   glBegin(GL_QUADS);
#define ZOOM_1 20.0
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
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat ambientLight[] = { 0.2f, 1, 0.2f, 1.0f };
    GLfloat diffuseLight[] = { 0.8f, 1, 0.8, 1.0f };
    GLfloat specularLight[] = { 0.5f, 1, 0.5f, 1.0f };
    GLfloat position[] = { -1.5f, 1.0f, -4.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
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
    glColorMaterial ( GL_FRONT_AND_BACK, GL_EMISSION ) ;
   glEnable ( GL_COLOR_MATERIAL ) ;
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
    for(auto o : this->entityHandler->dynamicEnts) {
        Entity* e = o.second;
        e->getOpenGLObject()->draw(e->getPose());
    }

    this->glCanvas->endDraw();

    this->glCanvas->updateGL();

    QCoreApplication::instance()->installEventFilter(new KeyboardInput(this->entityHandler));
}

