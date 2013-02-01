#include "entity.h"

Entity::Entity(OpenGLObject* openglobj, Pose* pose) {
    this->openglobj = openglobj;
    this->pose = pose;
}

void Entity::update (void) {
    if (physObject) {
        printf("I got updated!");
    }
}

OpenGLObject* Entity::getOpenGLObject() {
    return this->openglobj;
}

Pose* Entity::getPose() {
    return this->pose;
}
