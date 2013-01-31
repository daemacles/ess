#include <QDesktopWidget>

#include "entityhandler.h"
#include "simulator.h"
#include "glcanvas.h"

class GUI: public QWidget {
    private:
        Q_OBJECT
        EntityHandler* entityHandler;
        Simulator* sim;
        GLCanvas* glCanvas;

    public:
        GUI(EntityHandler* entityhandler, Simulator* sim);
        void setup();

        public slots:
            void draw();
};
