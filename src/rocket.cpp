#include "rocket.h"
#include <cmath>

// This multiplier will give the main engines a combined maximum thrust of 4G
const double Rocket::MAIN_MULT = 9.8 * 4.0 / 4.0;

// This multiplier will give the rotational engines each a thrust of 0.5G,
// for 1G combined by two of them.
const double Rocket::ROT_MULT = 9.8 * 2.0 / 4.0;

Rocket::Rocket (btVector3 startPos, btScalar mass) {
    ShapeHandler *sh = ShapeHandler::getHandler();
    if (!sh->hasShape("rocket01")) {
        // Load in the shapes to be used
        // sh->addMesh("rocket01", "../models/rocket01.stl", true);
        sh->addConvexHull("rocket01", "../models/rocket01.stl");
    }
    
    btCollisionShape *rocketShape = sh->getShape("rocket01");
    this->openglObject = sh->getMesh("rocket01")->openglobj;
    float color[4] = {1, 0, 0, 1};
    this->openglObject->setColor(color);

    engineFiredCount = 0;

    // Set up our beginning transform
    //btQuaternion rot(0,0,0,1);
    btTransform trans;
    trans.setIdentity();
    trans.setOrigin(startPos);
    trans.setRotation(btQuaternion(btVector3(0, 1, 0), -90.0/57.0));
  
    initRigidBody(mass, rocketShape, trans);

    rigidBody->setLinearFactor({1,1,0});
    rigidBody->setAngularFactor({0,0,1});

    init();
}
    
void Rocket::update (btScalar timeStep, btScalar time) {
    // First, save our current (old) pose
    poseHistory.push_back(pose);

    // Next parent's update, which will update our pose
    Entity::update(timeStep, time);   
}

std::vector<Pose>& Rocket::getPoseHistory() {
    return poseHistory;
}

void Rocket::fireEngine(int n, btScalar throttle) {
    // Count the number of times the engine has been fired,
    // in order for the gui to create the engine light
    engineFiredCount++;

    // Clamping -- I guess we don't have afterburner.
    if (throttle > 1.0) throttle = 1.0;
    if (throttle < 0.0) throttle = 0.0;

    // The rocket's orientation.
    btQuaternion ori = rigidBody->getOrientation();

    // The offset is given in world coordinates, which is why it is rotated by
    // the rocket's orientation to place it in the rocket's frame of
    // reference.
    btVector3 offset = enginePosition[n].rotate(ori.getAxis(), ori.getAngle());

    // The final rotation for the engine's thrust implicitly includes the
    // per-engine rotation, which is relative to the rocket's frame of
    // reference.
    btVector3 direction = engineForce[n].rotate(ori.getAxis(), ori.getAngle());

    // The impulse force is a vector of length impulseStrength along the world
    // y axis that is then rotated by the rotation calculated earlier to bring
    // it into the rocket's frame of reference.
    btScalar impulseStrength = throttle * engineStrength[n];
    btVector3 impulse = direction * impulseStrength;

    // Last but not least, apply the impulse.
    rigidBody->applyForce(impulse, offset);    
}

void Rocket::applyControl (const RocketControl &control) {
    rigidBody->setActivationState(ACTIVE_TAG);
    // rigidBody->setLinearVelocity({0,0,0}); // ROCKET CAN'T MOVE!!!!

    for (int i = 0; i < RocketControl::NUM_ENGINES; ++i) {
        fireEngine(i, control.engine[i]);
    }
}

void Rocket::init (void) {
    // POSITIONS
    // Main engines
    btScalar h_off = 0.9;       // horizontal offset
    btScalar v_off = -1.25;     // vertical offset
    enginePosition[MAIN1] = btVector3( h_off, v_off,  0);
    enginePosition[MAIN2] = btVector3(-h_off, v_off,  0);
    enginePosition[MAIN3] = btVector3(0,      v_off,  h_off);
    enginePosition[MAIN4] = btVector3(0,      v_off, -h_off);

    // Rotational engines
    h_off = 0.4;
    v_off = 0.0;
    enginePosition[ROT1] = btVector3( h_off, v_off, 0);
    enginePosition[ROT2] = btVector3(-h_off, v_off, 0);
    enginePosition[ROT3] = btVector3( h_off, v_off, 0);
    enginePosition[ROT4] = btVector3(-h_off, v_off, 0);

    // FORCES
    // Specified as a unit vector in the direction of "push" produced by this
    // engine.
    engineForce[MAIN1] = btVector3(0, 1, 0).normalize();
    engineForce[MAIN2] = btVector3(0, 1, 0).normalize();
    engineForce[MAIN3] = btVector3(0, 1, 0).normalize();
    engineForce[MAIN4] = btVector3(0, 1, 0).normalize();

    // Because the horizontal offset of the engines are along the x-axis, the
    // direction of their thrust must be perpendicular to this, i.e., along
    // the z-axis.
    engineForce[ROT1]  = btVector3(0, 0,  1).normalize();
    engineForce[ROT2]  = btVector3(0, 0, -1).normalize();
    engineForce[ROT3]  = btVector3(0, 0, -1).normalize();
    engineForce[ROT4]  = btVector3(0, 0,  1).normalize();

    // STRENGTHS - by default, the main motors can generate 2G of thrust
    // combined.
    engineStrength[MAIN1] = mass * MAIN_MULT;
    engineStrength[MAIN2] = mass * MAIN_MULT;
    engineStrength[MAIN3] = mass * MAIN_MULT;
    engineStrength[MAIN4] = mass * MAIN_MULT;
    engineStrength[ROT1] = mass * ROT_MULT;
    engineStrength[ROT2] = mass * ROT_MULT;
    engineStrength[ROT3] = mass * ROT_MULT;
    engineStrength[ROT4] = mass * ROT_MULT;
}

