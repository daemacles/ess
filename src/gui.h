#include <QDesktopWidget>

#include "entityhandler.h"
#include "simulator.h"

class GUI: public QWidget {
    private:
        EntityHandler* entityHandler;
        Simulator* sim;

    public:
        GUI(EntityHandler* entityhandler, Simulator* sim);
        void setup();
        void draw();
};
