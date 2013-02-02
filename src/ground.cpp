#include "ground.h"

Ground::Ground(btScalar width, btScalar length) {
    ShapeHandler *sh = ShapeHandler::getHandler();

    if (!sh->hasShape("ground")) {
        sh->addBox("ground", btVector3(width, 10, length));
    }                   
    initRigidBody(0.0, sh->getShape("ground"));
}
