#include "entity.h"

class Platform:public Entity {
    public:
        Platform(btVector3 startPos = btVector3(0,-9,0));
};
