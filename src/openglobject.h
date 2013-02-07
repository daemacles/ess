#ifndef _OPENGLOBJECT_H_
#define _OPENGLOBJECT_H_

#include <vector>
#include "LinearMath/btVector3.h"

#include "pose.h"


#include    <stdio.h>                         // Header File For Standard Input/Output ( NEW )

#ifndef PHYS_DEMO
#include <QtOpenGL>
#include "sprite.h"

struct polygon {
    float x, y, z;
};

class OpenGLObject {
    private:
        float color[4];
        Sprite* sprite;

    public:
        void setSprite(Sprite* sprite);
        void setColor(float* color);
        std::vector<btVector3*> polygons;
        void draw(Pose& pose);
        OpenGLObject(std::vector<btVector3*> polygons);

};

#else
class OpenGLObject {
    public:
    void setColor(float* color) {} ;
        //void draw(Pose* pose) { }
        //OpenGLObject(std::vector<btVector3*> polygons) { }
};
#endif


#endif
