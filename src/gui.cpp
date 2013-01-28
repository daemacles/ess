#include <QLabel>
#include <QFrame>
#include <QDesktopWidget>

#include "gui.h"
#include "glwidget.h"

GUI::GUI(EntityHandler* entityhandler, Simulator* sim) {
}

void GUI::setup() {

    QWidget* window = new QWidget;

    GLWidget* glCanvas = new GLWidget(window);
    glCanvas->resize(1024,768);
    glCanvas->draw();

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

    /*
    GLWidget* window = new GLWidget(window);
    //window->resize(320, 240);
    QLabel label1("Hello, world!", window);
    QLabel label2("Hello, world!", window);
    QLabel label3("Hello, world!", window);
    QLabel label3("Hello, world!", window);
    QLabel label1("Hello, world!", window);
    window->show();
    window->setWindowTitle(
        QApplication::translate("helloworld", "Hello World"));
    //return app.exec();
    */
}
