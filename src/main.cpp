#include <QApplication>

#include "gui.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    EntityHandler* entityHandler = new EntityHandler();
    Simulator* simulator = new Simulator(entityHandler);

    GUI* gui = new GUI(entityHandler, simulator);
    gui->setup();

    return app.exec();
}
