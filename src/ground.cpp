#include <iostream>

#include "ground.h"

Ground::Ground(btScalar width, btScalar length) {
    ShapeHandler *sh = ShapeHandler::getHandler();

    if (!sh->hasShape("ground")) {
        btVector3 extents(width, 1.0, length);
        sh->addBox("ground", extents);
    }                   
    initRigidBody(0.0, sh->getShape("ground"));
    rigidBody->setRestitution(0.1);
}
