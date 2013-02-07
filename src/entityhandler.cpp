
#include "entityhandler.h"
#include "shapehandler.h"
#include "objparser.h"
#include "entity.h"
#include "ground.h"
#include "rocket.h"
#include "gyrosensor.h"

EntityHandler::EntityHandler () {
    init();
}

// TODO: convert to use a config file instead of hard coding what to load.
void EntityHandler::init () {
    // Bring life forth into the world!
    addStatic("ground", new Ground());
    addDynamic("rocket", new Rocket());
    addSensor("gyro", new GyroSensor("Rocket gyro", dynamicEnts["rocket"]));

    dynamicEnts["rocket"]->getRigidBody()->setAngularVelocity({0,0,0});
}    

void EntityHandler::callUpdates (btScalar delta_t, btScalar time) {
    for (auto pr : dynamicEnts) {
        auto ent = pr.second;
        ent->update(delta_t, time);
    }
    for (auto pr : sensors) {
        auto sensor = pr.second;
        sensor->update(time);
    }
}

// little convenience function to free memory pointed to by an entityMap_t
void freeEnts (EntityHandler::entityMap_t &entmap) {
    for (auto pr : entmap) {
        Entity *ent = pr.second;
        btRigidBody *body = ent->getRigidBody();
        if (body->getMotionState()) {
            delete body->getMotionState();
        }
        delete body;
    }
    entmap.clear();
}

EntityHandler::~EntityHandler (void) {
    // Free memory from entities handled?
    freeEnts(dynamicEnts);
    freeEnts(staticEnts);
}
