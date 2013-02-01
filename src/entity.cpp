#include "entity.h"

Entity::Entity (btRigidBody *body, OpenGLObject *oglobj):
    physObject(body),
    openglObject(oglobj)
{
    // TODO?
}

void Entity::update (void) {
    if (physObject) {
        printf("I got updated!");
    }
}

OpenGLObject* Entity::getOpenGLObject() {
    return this->openglObject;
}

Pose& Entity::getPose() {
    return pose;
}
