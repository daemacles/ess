#include <iostream>

#include "ground.h"

Ground::Ground(btScalar width, btScalar length) {
    // ShapeHandler *sh = ShapeHandler::getHandler();

    // if (!sh->hasShape("ground")) {
    //     btVector3 extents(width, 1.0, length);
    //     sh->addBox("ground", extents);
    // }                   
    // initRigidBody(0.0, sh->getShape("ground"));
    // rigidBody->setRestitution(0.1);
    ShapeHandler *sh = ShapeHandler::getHandler();
    if (!sh->hasShape("mars")) {
        // Load in the shapes to be used
        sh->addMesh("mars", "mars_cut.stl", false);
    }
    
    btCollisionShape *groundShape = sh->getShape("mars");
    this->openglObject = sh->getMesh("mars")->openglobj;
    float color[4] = {0.5f, 0.35f, 0.05f, 1.0f};
    this->openglObject->setColor(color);

    // Set up our beginning transform
    //btQuaternion rot(0,0,0,1);
    btTransform trans;
    trans.setIdentity();
    trans.setOrigin(btVector3(-20,0,10));
    //trans.setRotation(btQuaternion(btVector3(1, 0, 0), 0));
  
    initRigidBody(0.0f, groundShape, trans);
}
