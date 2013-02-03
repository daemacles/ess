#ifndef _STLLOADER_H
#define _STLLOADER_H 1

#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <BulletCollision/CollisionShapes/btTriangleMesh.h>
#include "openglobject.h"

class BinaryReader;

class StlMesh : public btTriangleMesh {
    private:

    public:
    OpenGLObject* openglobj;
    StlMesh (const std::string &filename, bool removeDuplicateVertices=false);
    virtual ~StlMesh();
};

#endif
