#ifndef _GUI_H
#define _GUI_H

#include <QDesktopWidget>
#include <unordered_map>

#include "entityhandler.h"
#include "simulator.h"
#include "glcanvas.h"
#include "sprite.h"
#include "keyboardinput.h"

class GUI: public QWidget {
    // This class keeps track of all OpenGL and Qt drawing
    //
    private:
        Q_OBJECT

        Sprite* bgSprite; // Space image
        Sprite* bgGroundSprite; // Dirt image
        float planetRotation;

        unsigned int lastSeenEngineFire;
        float fireCountdown;
        GLuint backgroundTextureId;

        KeyboardInput* keyboardInput;

        EntityHandler* entityHandler;
        Simulator* simulator;
        GLCanvas* glCanvas;

        std::unordered_map<Sensor*, QLabel*> sensorLabelMap;
        QWidget* setupSensors();

        void loadRocketFireShape();

        void initBackgroundImage(Sprite* sprite);
        void drawBackground();
        void drawBackgroundImage(float x1, float x2, float y1, float y2, float depth, float rotation);
        void drawGroundBackground();
        void drawPoseHistory();

        void sunLight();
        void rocketEngineLight();


    public:

        GUI(EntityHandler* enthand, Simulator* sim);
        ~GUI ();
        void setup();

        public slots:
            void resetRocket();
            void draw();
};

#endif
