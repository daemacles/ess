#ifndef _ROCKET_H
#define _ROCKET_H

#include <vector>
#include <LinearMath/btVector3.h>

#include "entity.h"
#include "pose.h"
#include "rocketcontrol.h"

class Rocket : public Entity {
    public:
    // This multiplier will give the main engines a combined maximum thrust of 2G
    static const double MAIN_MULT;

    // This multiplier will give the rotational engines each a thrust of 0.5G,
    // for 1G combined by two of them.
    static const double ROT_MULT;
    
    protected:
    std::vector<Pose> poseHistory;
    btVector3 enginePosition [RocketControl::NUM_ENGINES];
    btVector3 engineForce    [RocketControl::NUM_ENGINES];
    btScalar  engineStrength [RocketControl::NUM_ENGINES];

    // MAIN1..4 point straight down,
    // MAIN1 and 2 are opposite each other, along the x-axis
    // MAIN3 and 4 are opposite each other, along the z-axis
    // ROT1 and ROT2 spin the same direction
    // ROT1 and ROT4 push the same direction
    enum engineName { MAIN1=0, MAIN2, MAIN3, MAIN4,
                      ROT1,    ROT2,  ROT3,  ROT4 };

    public:
    Rocket (btVector3 startPos = btVector3(0,1,-1),
            btScalar mass = 5.0);

    void update (btScalar timeStep, btScalar time);
    std::vector<Pose>& getPoseHistory ();

    /// Applies user controls
    void applyControl (const RocketControl &control);

    private:
    void init ();
    void fireEngine(int n, btScalar throttle);
};

#endif
