#ifndef _ENTITY_H
#define _ENTITY_H

#include <btBulletDynamicsCommon.h>

#include "shapehandler.h"
#include "openglobject.h"
#include "pose.h"

/// This class represents an entity in the world
class Entity {
    protected:
    Pose pose;
    btRigidBody *rigidBody;    // Handle to this entity in bullet
    OpenGLObject *openglObject;
    double mass;

    public:
    Entity (btRigidBody *body=nullptr, 
            OpenGLObject *oglobj=nullptr);
    virtual ~Entity ();

    OpenGLObject* getOpenGLObject ();
    btRigidBody* getRigidBody ();
    Pose& getPose();
    
    virtual void update (btScalar timeStep, btScalar time);

    protected:
    virtual void initRigidBody (btScalar _mass, btCollisionShape *shape,
                                const btTransform &trans = btTransform::getIdentity());
};

#endif
