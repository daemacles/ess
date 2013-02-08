#ifndef _STLLOADER_H
#define _STLLOADER_H 1

#include <string>
#include "openglobject.h"

class BinaryReader;
class btTriangleMesh;

class StlMesh : public btTriangleMesh {
    private:

    public:
    OpenGLObject* openglobj;
    StlMesh (const std::string &filename, bool removeDuplicateVertices=false);
    virtual ~StlMesh();
};

#endif
