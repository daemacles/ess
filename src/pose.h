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
    int tick;                   ///< a time stamp of sorts

    Pose () {}
    Pose (btRigidBody *b);       // Copies pertinant information over
};

#endif
