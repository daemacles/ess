#ifndef _SIMULATOR_H
#define _SIMULATOR_H 1

#include "btBulletDynamicsCommon.h"

#include "entityhandler.h"

void simCallback(btDynamicsWorld *world, btScalar timeStep);

class Simulator {
    private:
    EntityHandler *entities;

    public:
    Simulator (EntityHandler *_ents): entities(_ents) {};
    void callback (btScalar timeStep);
};

#endif
