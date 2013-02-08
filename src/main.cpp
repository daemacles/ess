#include <cstdlib>
#include <chrono>
#include <thread>

#include <QApplication>

#include "gui.h"
#include "zmqhandler.h"

int phys_main(int, char**);

int main(int argc, char *argv[])
{
    if (argc != 2) exit(1);
    EntityHandler entityHandler;
    ZMQHandler networkHandler(atoi(argv[1]));
    Simulator simulator(&entityHandler, &networkHandler);
    simulator.start();

    // std::chrono::milliseconds dura(1000);
    // std::this_thread::sleep_for(dura);
    
    QApplication app(argc, argv);
    GUI* gui = new GUI(&entityHandler, &simulator);
    gui->setup();

    app.exec();

    simulator.stop();
    return 0;
}
