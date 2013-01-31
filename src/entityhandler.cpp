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
    }

    Entity* e = new Entity(globj, NULL);

    this->entities.push_back(e);
}

std::vector<Entity*> EntityHandler::getEntities() {
    return this->entities;
}
