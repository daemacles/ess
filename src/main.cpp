#include <QApplication>

#include "gui.h"
#include "zmqhandler.h"

int phys_main(int, char**);

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    EntityHandler* entityHandler = new EntityHandler();
    ZMQHandler* networkHandler = new ZMQHandler(6767);
    Simulator* simulator = new Simulator(entityHandler, networkHandler);

    GUI* gui = new GUI(entityHandler, simulator);
    gui->setup();

    app.exec();

    delete entityHandler;
    delete simulator;

    phys_main(argc, argv);
    return 0;
}
