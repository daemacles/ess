
#include "btBulletDynamicsCommon.h"

typedef btVector3 vec3;

class Pose {
    public:
        vec3 pos;
        vec3 vel;
        vec3 acc;
        vec3 orientation;
};
