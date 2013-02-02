#include <memory>

#include "entity.h"

Entity::Entity (btRigidBody *body, OpenGLObject *oglobj):
    rigidBody(body),
    openglObject(oglobj)
{
    // TODO?
}

void Entity::update (void) {
    if (rigidBody) {
        // printf("I got updated!");
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

void Entity::initRigidBody (btScalar mass, btCollisionShape *shape, btTransform *trans) {
    // Create a default transform if one is not provided to us
    if (trans == nullptr) {
        std::unique_ptr<btTransform> utrans(new btTransform());
        trans = utrans.get();
        trans->setIdentity();
        //trans->setOrigin(btVector3(0,0,0));
    }
    
    btDefaultMotionState *myMotionState = new btDefaultMotionState(*trans);
    btVector3 localInertia(0,0,0);
    if (mass != 0.0)
        shape->calculateLocalInertia(mass, localInertia);

    btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState,
                                                   shape, localInertia);
    rigidBody = new btRigidBody(cInfo);
    rigidBody->setRestitution(0.0);
    rigidBody->setContactProcessingThreshold(BT_LARGE_FLOAT);
}

Entity::~Entity() {
    delete rigidBody;
    rigidBody = nullptr;
    delete openglObject;
    openglObject = nullptr;
}
