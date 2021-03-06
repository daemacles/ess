#include <memory>
#include <cstdio>

#include "entity.h"

Entity::Entity (btRigidBody *body, OpenGLObject *oglobj):
    rigidBody(body),
    openglObject(oglobj)
{
    // TODO?
}

void Entity::update (btScalar timeStep, btScalar time) {
    if (rigidBody) {
        pose.update(rigidBody, time);
        //printf("I got updated! %f\n", timeStep);
    }
}

OpenGLObject* Entity::getOpenGLObject() {
    return openglObject;
}

btRigidBody* Entity::getRigidBody() {
    return rigidBody;
}

Pose& Entity::getPose() {
    return pose;
}

void Entity::initRigidBody (btScalar _mass, btCollisionShape *shape,
                            const btTransform &trans) {
    btDefaultMotionState *myMotionState = new btDefaultMotionState(trans);
    btVector3 localInertia(0,0,0);
    mass = _mass;
    if (mass != 0.0)
        shape->calculateLocalInertia(mass, localInertia);

    btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState,
                                                   shape, localInertia);
    rigidBody = new btRigidBody(cInfo);
    rigidBody->setRestitution(0.0);
    rigidBody->setContactProcessingThreshold(BT_LARGE_FLOAT);

    // Create the initial pose.  This is needed for static entities whose
    // 'update' method never gets called.
    pose.update(rigidBody, 0.0);
}

Entity::~Entity() {
    // printf("Deleted an entity\n");
    delete rigidBody;
    rigidBody = nullptr;
    delete openglObject;
    openglObject = nullptr;
}
