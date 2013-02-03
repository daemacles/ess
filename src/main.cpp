#include <QApplication>

#include "gui.h"

int phys_main(int, char**);

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    EntityHandler* entityHandler = new EntityHandler();
    Simulator* simulator = new Simulator(entityHandler);

    GUI* gui = new GUI(entityHandler, simulator);
    gui->setup();

    app.exec();

    delete entityHandler;
    delete simulator;

    phys_main(argc, argv);
    return 0;
}
