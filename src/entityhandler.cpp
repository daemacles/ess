#include "entityhandler.h"

#include <vector>

#include "objparser.h"
#include "entity.h"

EntityHandler::EntityHandler() {
    OBJParser* parser = new OBJParser;
    std::string rocket_file = "rocket.obj";

    OpenGLObject* globj = parser->parse(rocket_file);

    if(!globj) {
        printf("GICK EJ ATT LADDA\n");

    Pose* p = new Pose;
    p->pos.x = -2;
    p->pos.y = -0.5;
    p->pos.z = 0;

    Entity* e = new Entity(globj, p);

    this->entities.push_back(e);
}

void EntityHandler::callUpdates (void) {
    for (auto p : dynamicEnts) {
        auto ent = p.second;
        ent->update();
    }
}

std::vector<Entity*> EntityHandler::getEntities() {
    return this->entities;
}
