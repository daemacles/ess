#include "entity.h"

Entity::Entity(OpenGLObject* openglobj, Pose* pose) {
    this->openglobj = openglobj;
    this->pose = pose;
}

OpenGLObject* Entity::getOpenGLObject() {
    return this->openglobj;
}
