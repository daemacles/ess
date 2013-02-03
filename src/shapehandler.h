#ifndef _SHAPEHANDLER_H
#define _SHAPEHANDLER_H 1

#include <map>
#include <string>
#include <btBulletDynamicsCommon.h> // main Bullet include file, contains most
                                    // common include files.
#include "stlmesh.h"

/*! \class ShapeHandler
 * Maintains a store of btCollisionShapes that can be assigned to rigid
 * bodies.  It also manages the memory of any btCollisionShapes that it
 * tracks.  This class uses the singleton pattern, so there is only ever one
 * ShapeHandler instance available.
 */
class ShapeHandler {
    protected:
    static ShapeHandler *singleton;

    /// Shapes available for use by the physics system
    std::map<std::string, btCollisionShape*> shapes;

    /// Keeps track of memory used by the meshes backing any shapes like
    /// btGImpactShape, btBvhTriangleShape, or btHeightfieldTerrainShape
    std::map<btCollisionShape*, StlMesh*> meshes;
    
    public:
    virtual ~ShapeHandler ();
    
    /// Get a pointer to the shape handler
    static ShapeHandler* getHandler();

    /// Returns a pointer to a named shape
    btCollisionShape *getShape(std::string name);

    StlMesh *getMesh(std::string name);

    ///
    /// \param name handle for this shape
    /// \param filename binary STL mesh data for this mesh
    void addMesh (std::string name, std::string filename);

    // name - handle for this shape
    // extents - x: width, y: height, z: length
    void addBox (std::string name, btVector3 extents);

    bool hasShape(std::string name);

    private:
    ShapeHandler () {}
};

#endif
