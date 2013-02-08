#include <QDesktopWidget>
#include <unordered_map>

#include "entityhandler.h"
#include "simulator.h"
#include "glcanvas.h"
#include "sprite.h"

class GUI: public QWidget {
    private:
        Q_OBJECT

        Sprite* bgSprite; // Space image
        Sprite* bgGroundSprite; // Dirt image
        float planetRotation;

        unsigned int lastSeenEngineFire;
        float fireCountdown;

        EntityHandler* entityHandler;
        Simulator* simulator;
        GLCanvas* glCanvas;

        std::unordered_map<Sensor*, QLabel*> sensorLabelMap;
        QWidget* setupSensors();

        void loadRocketFireShape();

        void drawBackground();
        void drawBackgroundImage(Sprite* sprite, float x1, float x2, float y1, float y2, float depth, float rotation);
        void drawGroundBackground();

        void sunLight();
        void rocketEngineLight();

    public:

        GUI(EntityHandler* enthand, Simulator* sim);
        ~GUI ();
        void setup();

        public slots:
            void draw();
};
