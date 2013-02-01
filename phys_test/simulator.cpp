#include <cstdio>

#include "simulator.h"

void simCallback(btDynamicsWorld *world, btScalar timeStep) {
    Simulator *sim = static_cast<Simulator*>(world->getWorldUserInfo());
    sim->callback(timeStep);
}

void Simulator::callback (btScalar timeStep) {
    entities->callUpdates();
}
