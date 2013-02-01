#ifndef _STLLOADER_H
#define _STLLOADER_H 1

#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <BulletCollision/CollisionShapes/btTriangleMesh.h>

class BinaryReader;

class StlLoader {
    private:
    std::unique_ptr<btTriangleMesh> m_mesh;

    public:
    StlLoader (const std::string &filename);
    virtual ~StlLoader();

    btTriangleMesh* getMesh();
};

#endif
