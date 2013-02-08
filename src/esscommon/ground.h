#ifndef _GROUND_H
#define _GROUND_H 1

#include "entity.h"

class Ground: public Entity {
    private:

    public:
    Ground(btScalar width=110.0, btScalar length=110.0);
};

#endif
