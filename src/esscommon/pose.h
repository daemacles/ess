#ifndef _POSE_H
#define _POSE_H 1

#include "btBulletDynamicsCommon.h"

typedef btVector3 vec3;

class Pose {
    public:
    btTransform worldTransform;
    vec3 linVel;
    vec3 angVel;
    vec3 linForce;
    vec3 torque;
    btScalar timestamp;                   

    Pose () {}
    Pose (btRigidBody *b, btScalar time=0.0); // Copies pertinant information

    void update(btRigidBody *b, btScalar time=0.0);
};

#endif
