
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
    // Load in the shapes to be used
    ShapeHandler *sh = ShapeHandler::getHandler();
    sh->addMesh("rocket", "../models/rocket01.stl");
    sh->addBox("ground", btVector3(110.0, 1.0, 110.0));

    // Create the rigid bodies
    //Ground *g = new Ground();
    //staticEnts["ground"] = g;

    Rocket *r = new Rocket();
    dynamicEnts["rocket"] = r;
}    

void EntityHandler::callUpdates (void) {
    for (auto pr : dynamicEnts) {
        auto ent = pr.second;
        ent->update();
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
