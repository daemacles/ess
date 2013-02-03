#include "rocket.h"

Rocket::Rocket (btVector3 startPos, btScalar mass) {
    ShapeHandler *sh = ShapeHandler::getHandler();
    if (!sh->hasShape("rocket01")) {
        // Load in the shapes to be used
        sh->addMesh("rocket01", "../models/rocket01.stl");
    }
    
    btCollisionShape *groundShape = sh->getShape("rocket01");
    this->openglObject = sh->getMesh("rocket01")->openglobj;

    // Set up our beginning transform
    //btQuaternion rot(0,0,0,1);
    btTransform trans;
    trans.setIdentity();
    trans.setOrigin(startPos);
  
    initRigidBody(5.0, groundShape, &trans);
}
    
