#ifndef _SIMULATOR_H
#define _SIMULATOR_H 1

#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h"

#include "entityhandler.h"

void simCallback(btDynamicsWorld *world, btScalar timeStep);

class Simulator {
    protected:
    EntityHandler                  *entities;
    btDynamicsWorld                *dynamicsWorld;
    btDefaultCollisionConfiguration *collisionConfiguration;
    btCollisionDispatcher          *dispatcher;
    btBroadphaseInterface          *broadphase;
    btConstraintSolver             *solver;
    btScalar                       elapsedTime; ///< time since beginning of world
    
    public:
    Simulator (EntityHandler *_ents);
    virtual ~Simulator ();
    
    void callback (btScalar timeStep);
    btDynamicsWorld* getDynamicsWorld ();
};
#endif
