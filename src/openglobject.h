#ifndef _OPENGLOBJECT_H_
#define _OPENGLOBJECT_H_

#include <QtOpenGL>
#include <vector>
#include "LinearMath/btVector3.h"

struct polygon {
    float x, y, z;
};

class OpenGLObject {
    private:
    
    public:
    std::vector<btVector3*> polygons;
    void draw(float x, float y, float z);
    OpenGLObject(std::vector<btVector3*> polygons);
};

#endif
