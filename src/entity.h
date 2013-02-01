#ifndef _ENTITY_H
#define _ENTITY_H

// This class represents an entity in the world

#include <BulletDynamics/Dynamics/btRigidBody.h>

#include "pose.h"

class Entity {
    private:
    Pose pose;
    btRigidBody *physObject;    // Handle to this entity in bullet
    
    public:
    Entity (btRigidBody *body=nullptr): physObject(body) {};
    void update (void);
};

#endif
