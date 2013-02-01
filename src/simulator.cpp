#include <cstdio>
#include <vector>

#include "simulator.h"

void simCallback(btDynamicsWorld *world, btScalar timeStep) {
    Simulator *sim = static_cast<Simulator*>(world->getWorldUserInfo());
    sim->callback(timeStep);
}

Simulator::Simulator() {
    this->sensors.push_back(new Sensor);
    this->sensors.push_back(new Sensor);
}

void Simulator::callback (btScalar timeStep) {
    entities->callUpdates();
}

std::vector<Sensor*> Simulator::getSensors() { 
    return this->sensors;
}
