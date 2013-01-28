#include <QApplication>

#include "gui.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GUI* gui = new GUI(NULL, NULL);
    gui->setup();

    return app.exec();
}
