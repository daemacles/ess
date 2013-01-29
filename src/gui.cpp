#include <QLabel>
#include <QFrame>
#include <QDesktopWidget>

#include "gui.h"
#include "glwidget.h"
#include "openglobject.h"

GUI::GUI(EntityHandler* entityhandler, Simulator* sim) {
}

void GUI::setup() {

    QWidget* window = this;

    GLWidget* glCanvas = new GLWidget(window);
    glCanvas->setMinimumSize(768,480);
    //glCanvas->resize(700,500);
    glCanvas->draw();

    //OpenGLObject* globj = new OpenGLObject;
    //globj->draw(0,0,0);

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
