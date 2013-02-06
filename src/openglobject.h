#ifndef _OPENGLOBJECT_H_
#define _OPENGLOBJECT_H_

#include <vector>
#include "LinearMath/btVector3.h"

#include "pose.h"


#include    <stdio.h>                         // Header File For Standard Input/Output ( NEW )

#ifndef PHYS_DEMO
#include <QtOpenGL>

struct polygon {
    float x, y, z;
};

class OpenGLObject {
    private:
        btVector3 color;

    public:
        void setColor(btVector3 color);
        std::vector<btVector3*> polygons;
        void draw(Pose& pose);
        OpenGLObject(std::vector<btVector3*> polygons);

};

#else
class OpenGLObject {
    public:
        //void draw(Pose* pose) { }
        //OpenGLObject(std::vector<btVector3*> polygons) { }
};
#endif


#endif
