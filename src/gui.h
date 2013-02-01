#include <QDesktopWidget>
#include <unordered_map>

#include "entityhandler.h"
#include "simulator.h"
#include "glcanvas.h"

class GUI: public QWidget {
    private:
        Q_OBJECT
        EntityHandler* entityHandler;
        Simulator* simulator;
        GLCanvas* glCanvas;
        std::unordered_map<Sensor*, QLabel*> sensorLabelMap;
        QWidget* setupSensors();

    public:
        GUI(EntityHandler* entityhandler, Simulator* sim);
        void setup();

        public slots:
            void draw();
};
