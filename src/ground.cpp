#include "ground.h"

Ground::Ground(btScalar width, btScalar length) {
    ShapeHandler *sh = ShapeHandler::getHandler();

    if (!sh->hasShape("ground")) {
        sh->addBox("ground", btVector3(width, 1.0, length));
    }                   
    initRigidBody(0.0, sh->getShape("ground"));
    rigidBody->setRestitution(0.1);
}
