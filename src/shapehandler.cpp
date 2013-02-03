#include <BulletCollision/Gimpact/btGImpactShape.h>

#include "stlmesh.h"
#include "shapehandler.h"

// Initialize class static reference to the singleton object
ShapeHandler* ShapeHandler::singleton = nullptr;

ShapeHandler* ShapeHandler::getHandler () {
    if (singleton == nullptr) {
        singleton = new ShapeHandler();
    }

    return singleton;
}

btCollisionShape* ShapeHandler::getShape (std::string name) {
    return shapes.at(name);
}

StlMesh* ShapeHandler::getMesh (std::string name) {
    return meshes.at(shapes.at(name));
}

//  !!!!! BUG?
// 
// What to do if someone adds a mesh with the same name?  I think this should
// just be disallowed, because we aren't tracking which objects reference a
// shape, so replacing that shape (and freeing its memory) is a no-no.  Or we
// could use smart pointers?

// Loads a mesh from disk in STL format and creates a shape from it.
void ShapeHandler::addMesh (std::string name, std::string filename) {
    // Load the mesh from disk and save it in the meshes map
    StlMesh *mesh = new StlMesh(filename);
    btGImpactMeshShape *shape = new btGImpactMeshShape(mesh);
    shape->updateBound();

    shapes[name] = shape;
    meshes[shape] = mesh;
}

void ShapeHandler::addBox (std::string name, btVector3 extents) {
    btBoxShape *box = new btBoxShape(extents);
    shapes[name] = box;
}

bool ShapeHandler::hasShape(std::string name) {
    return shapes.find(name) != shapes.end();
}

ShapeHandler::~ShapeHandler () {
    // Clean up the shapes we've loaded
    for (auto &pr : shapes) {
        delete pr.second;
    }
    // Clean up meshes we've loaded
    for (auto &pr : meshes) {
        delete pr.second;
    }
}
