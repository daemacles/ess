#include <QLabel>
#include <QFrame>
#include <QDesktopWidget>
#include <string>
#include <math.h>
#include <time.h>

#include "gui.h"
#include "entityhandler.h"
#include "glcanvas.h"
#include "openglobject.h"

float ff = 0.0;

void draw_entity_openglob(Entity* e) {
    Pose* pose = e->getPose();
    e->getOpenGLObject()->draw(sin(ff), 0, 0);
    ff += 0.05;
    //e->getOpenGLObject()->draw(pose->pos.x, pose->pos.y, pose->pos.z);
}

GUI::GUI(EntityHandler* entityhandler, Simulator* sim) {
    this->entityHandler = new EntityHandler();
}

void GUI::setup() {

    QWidget* window = this;

    this->glCanvas = new GLCanvas(window);
    this->glCanvas->setMinimumSize(1024,480);



    this->glCanvas->beginDraw();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(draw()));
    timer->start(1);


    QVBoxLayout* vlayout = new QVBoxLayout;

    QWidget* buttonRow = new QWidget;

    QPushButton *resetButton = new QPushButton("Reset");
    QPushButton *button1= new QPushButton("Reset");
    QPushButton *button2= new QPushButton("Reset");
    QPushButton *button3= new QPushButton("Reset");
    QPushButton *button4= new QPushButton("Reset");

    vlayout->addWidget(this->glCanvas);
    vlayout->addWidget(buttonRow);

    QHBoxLayout* buttonRowLayout = new QHBoxLayout;

    buttonRowLayout->addWidget(resetButton);
    buttonRowLayout->addWidget(button1);
    buttonRowLayout->addWidget(button2);
    buttonRowLayout->addWidget(button3);
    buttonRowLayout->addWidget(button4);
    buttonRow->setLayout(buttonRowLayout);

    window->setLayout(vlayout);
    window->show();
}

void GUI::draw() {

    //glCanvas->resize(700,500);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    //glCanvas->draw();
    //
    //OpenGLObject* globj = new OpenGLObject(NULL);
    //

    draw_entity_openglob(this->entityHandler->getEntities()[0]);
    //this->entityHandler->getEntities()[0]->getOpenGLObject()->draw(0,0,0);

    //globj->draw(0,0,0);

    this->glCanvas->endDraw();

    this->glCanvas->updateGL();
}
