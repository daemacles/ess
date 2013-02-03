
#include "entityhandler.h"
#include "shapehandler.h"
#include "objparser.h"
#include "entity.h"
#include "ground.h"
#include "rocket.h"

EntityHandler::EntityHandler () {
    init();
}

// TODO: convert to use a config file instead of hard coding what to load.
void EntityHandler::init () {
    // Create the rigid bodies
    staticEnts["ground"] = new Ground();
    dynamicEnts["rocket"] = new Rocket();
}    

void EntityHandler::callUpdates (btScalar timeStep, btScalar time) {
    for (auto pr : dynamicEnts) {
        auto ent = pr.second;
        ent->update(timeStep, time);
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
