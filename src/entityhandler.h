#ifndef _ENTITYHANDLER_H_
#define _ENTITYHANDLER_H_

#include <vector>

#include "entity.h"

class EntityHandler {
    private:
        std::vector<Entity*> entities;
    public:
        EntityHandler();
        std::vector<Entity*> getEntities();
};

#endif
