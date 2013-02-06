#ifndef _ROCKET_H
#define _ROCKET_H

#include <vector>
#include <LinearMath/btVector3.h>

#include "entity.h"
#include "pose.h"

class Rocket : public Entity {
    protected:
    std::vector<Pose> poseHistory;

    public:
    Rocket (btVector3 startPos = btVector3(0,0,0),
            btScalar mass = 5.0);

    void update (btScalar timeStep, btScalar time);
    std::vector<Pose>& getPoseHistory ();
};

#endif
