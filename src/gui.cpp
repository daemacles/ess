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
#include "pose.h"

#define ZOOM_1 50.0f

GUI::GUI(EntityHandler* enthand, Simulator* sim):
    entityHandler(enthand), simulator(sim)
{

    planetRotation = 0.0f;
    lastSeenEngineFire = 0;
}

void GUI::loadRocketFireShape() {
    ShapeHandler *sh = ShapeHandler::getHandler();
    if (!sh->hasShape("rocket_fire")) {
        sh->addConvexHull("rocket_fire", "../models/fire.stl");
    }
}

void GUI::setup() {
    keyboardInput = new KeyboardInput(this->entityHandler);

    bgSprite = Sprite::loadFromFile("stars.bmp");
    //bgGroundSprite = Sprite::loadFromFile("dirt.bmp");
    initBackgroundImage(bgSprite);

    loadRocketFireShape();

    QWidget* window = this;

    // GL screen widget
    this->glCanvas = new GLCanvas(window);
    this->glCanvas->setMinimumSize(GL_WIDTH,GL_HEIGHT);
    this->glCanvas->beginDraw();

    // Set up timer to update GL screen
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(draw()));
    timer->start(10);

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

void GUI::initBackgroundImage(Sprite* sprite) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &backgroundTextureId);
}

void GUI::drawBackgroundImage(float x1, float y1, float x2, float y2, float depth, float rotation) {
    Sprite* sprite = bgSprite;

    glPushMatrix();
    glLoadIdentity();
    glBindTexture(GL_TEXTURE_2D, backgroundTextureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sprite->width, 
            sprite->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
            sprite->data);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glBindTexture(GL_TEXTURE_2D, backgroundTextureId);

    glBegin(GL_QUADS);
        glTexCoord2f(0.75 + rotation, 0.0); glVertex3f(x1, y1, depth);
        glTexCoord2f(0.75 + rotation, 1.0); glVertex3f(x1, y2, depth);
        glTexCoord2f(1.0f + rotation, 1.0); glVertex3f(x2, y2, depth);
        glTexCoord2f(1.0f + rotation, 0.0); glVertex3f(x2, y1, depth);
    glEnd();

    glFlush();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

void GUI::drawBackground() {
    this->drawBackgroundImage(-ZOOM_1, -ZOOM_1+5, ZOOM_1, ZOOM_1+5, -99.0f, planetRotation);
}

void GUI::drawGroundBackground() {
    this->drawBackgroundImage(-ZOOM_1, -ZOOM_1+5, ZOOM_1, 0, -98.0f, 0);
}

void GUI::sunLight() {
#define SUN_LIGHT_STRENGHT 0.3f
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat ambientLight[] = {
        SUN_LIGHT_STRENGHT,
        SUN_LIGHT_STRENGHT,
        SUN_LIGHT_STRENGHT*0.8f
    };
    GLfloat position[] = {
        ZOOM_1,
        10.0f,
        20.0f,
        1.0f
    };

    //glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.4f);
    //glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.01);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.8f);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, ambientLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void GUI::rocketEngineLight() {
#define ENGINE_LIGHT_STRENGTH 1.0f
    Rocket* rocket = static_cast<Rocket*>(entityHandler->dynamicEnts["rocket"]);
    Pose pose = rocket->getPose();

    if(fireCountdown < 0.01f) {
        if(rocket->engineFiredCount == lastSeenEngineFire) {
            glDisable(GL_LIGHT1);
            return;
        } else {
            fireCountdown = 1.0f;
        }
    }
    fireCountdown -= 0.08f;

    lastSeenEngineFire = rocket->engineFiredCount;

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);

    GLfloat ambientLight[] = {
        fireCountdown*ENGINE_LIGHT_STRENGTH*1.0f,
        fireCountdown*ENGINE_LIGHT_STRENGTH*1.0f,
        fireCountdown*ENGINE_LIGHT_STRENGTH*0.0f,
    };
    GLfloat position[] = {
        pose.worldTransform.getOrigin().x(),
        pose.worldTransform.getOrigin().y(),
        pose.worldTransform.getOrigin().z()
    };


    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.0);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.01);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.01);

    glLightfv(GL_LIGHT1, GL_DIFFUSE, ambientLight);
    glLightfv(GL_LIGHT1, GL_POSITION, position);

    ShapeHandler *sh = ShapeHandler::getHandler();
    OpenGLObject* rocketFireOpenGLObject = sh->getMesh("rocket_fire")->openglobj;
    rocketFireOpenGLObject->setSprite(NULL);
    rocketFireOpenGLObject->draw(rocket->getPose());
    return;
}

void GUI::draw() {
    // This function draws all objects in the world and updates the OpenGL
    // canvas

    // Update physics
    //this->simulator->stepSimulation(1./60.);
    //

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    // Draw space image
    this->drawBackground();
    planetRotation += -0.00003f;

    // Draw moon dirt image
    //this->drawGroundBackground();
    //

    drawPoseHistory();

    sunLight();
    rocketEngineLight();

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
    /*
    delete keyboardInput;
    keyboardInput = new KeyboardInput(this->entityHandler);
    QCoreApplication::instance()->installEventFilter(keyboardInput);
    */
}

void GUI::drawPoseHistory() {
    Rocket* rocket = static_cast<Rocket*>(entityHandler->dynamicEnts["rocket"]);
    glBegin(GL_LINE_STRIP);
        float color[] = {1.0f, 1.0f, 1.0f};
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
        for(auto pose: rocket->poseHistory) {
            glVertex3f(
                    pose.worldTransform.getOrigin().x(),
                    pose.worldTransform.getOrigin().y(),
                    pose.worldTransform.getOrigin().z()
                    );
        }
    glEnd();
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

GUI::~GUI() {
}
