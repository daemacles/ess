#include <QLabel>
#include <QFrame>
#include <QDesktopWidget>
#include <string>

#include "gui.h"
#include "entityhandler.h"
#include "glwidget.h"
#include "openglobject.h"

void draw_entity_openglob(Entity* e) {
    Pose* pose = e->getPose();
    e->getOpenGLObject()->draw(pose->pos.x, pose->pos.y, pose->pos.z);
}

GUI::GUI(EntityHandler* entityhandler, Simulator* sim) {
    this->entityHandler = new EntityHandler();
}

void GUI::setup() {

    QWidget* window = this;

    GLWidget* glCanvas = new GLWidget(window);
    glCanvas->setMinimumSize(768,480);


    //glCanvas->resize(700,500);
    glCanvas->beginDraw();
    //glCanvas->draw();
    //
    //OpenGLObject* globj = new OpenGLObject(NULL);
    //

    draw_entity_openglob(this->entityHandler->getEntities()[0]);
    //this->entityHandler->getEntities()[0]->getOpenGLObject()->draw(0,0,0);

    //globj->draw(0,0,0);

    glCanvas->endDraw();


    QVBoxLayout* vlayout = new QVBoxLayout;

    QWidget* buttonRow = new QWidget;

    QPushButton *resetButton = new QPushButton("Reset");
    QPushButton *button1= new QPushButton("Reset");
    QPushButton *button2= new QPushButton("Reset");
    QPushButton *button3= new QPushButton("Reset");
    QPushButton *button4= new QPushButton("Reset");

    vlayout->addWidget(glCanvas);
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

}
