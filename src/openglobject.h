#ifndef _OPENGLOBJECT_H_
#define _OPENGLOBJECT_H_

#include <QtOpenGL>
#include <vector>

struct polygon {
    float x, y, z;
};

class OpenGLObject {
    private:
    std::vector<polygon> polygons;
    
    public:
    void draw(float x, float y, float z);
    OpenGLObject(std::vector<polygon> polygons);
};

#endif
