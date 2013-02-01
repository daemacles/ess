#include <QApplication>

#include "gui.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GUI* gui = new GUI(NULL, new Simulator);
    gui->setup();

    return app.exec();
}
