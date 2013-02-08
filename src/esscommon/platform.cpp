#include "platform.h"

Platform::Platform(btVector3 startPos) {
    ShapeHandler *sh = ShapeHandler::getHandler();
    if (!sh->hasShape("platform")) {
        // Load in the shapes to be used
        sh->addMesh("platform", "platform.stl", false);
    }
    
    btCollisionShape *platformShape = sh->getShape("platform");
    this->openglObject = sh->getMesh("platform")->openglobj;
    float color[4] = {0.3, 0.3, 0.3, 1};
    this->openglObject->setColor(color);

    // Set up our beginning transform
    //btQuaternion rot(0,0,0,1);
    btTransform trans;
    trans.setIdentity();
    trans.setOrigin(startPos);
    trans.setRotation(btQuaternion(btVector3(0, 1, 0), -90.0/57.0));
  
    initRigidBody(0.0, platformShape, trans);
}
