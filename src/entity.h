#ifndef _ENTITY_H
#define _ENTITY_H

// This class represents an entity in the world

#include <BulletDynamics/Dynamics/btRigidBody.h>

#include "openglobject.h"
#include "pose.h"

class Entity {
    private:
    Pose pose;
    btRigidBody *physObject;    // Handle to this entity in bullet
    OpenGLObject *openglobj;
    public:
    Entity (btRigidBody *body=nullptr, 
            OpenGLObject *oglobj=nullptr): physObject(body) {};
    OpenGLObject* getOpenGLObject();
	Pose* getPose();
    void update (void);
};
