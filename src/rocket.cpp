#include "rocket.h"
#include <cmath>

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

    // Set up our beginning transform
    //btQuaternion rot(0,0,0,1);
    btTransform trans;
    trans.setIdentity();
    trans.setOrigin(startPos);
    trans.setRotation(btQuaternion(btVector3(0, 1, 0), -90.0/57.0));
  
    initRigidBody(mass, rocketShape, trans);

    init();
}
    
void Rocket::update (btScalar timeStep, btScalar time) {
    // First, save our current (old) pose
    poseHistory.push_back(pose);

    // Next parent's update, which will update our pose
    Entity::update(timeStep, time);   

    rigidBody->setActivationState(ACTIVE_TAG);
    // rigidBody->setLinearVelocity({0,0,0}); // ROCKET CAN'T MOVE!!!!

    // No spinning! (a controller)
    btScalar xangErr = pose.angVel.x();
    btScalar yangErr = pose.angVel.y();
    btScalar zangErr = pose.angVel.z();

    // Rotation engines
    btScalar CWSpin = 0.0;
    btScalar CCWSpin = 0.0;
    if (yangErr > 0.0) CWSpin  = 0.1 + yangErr;
    if (yangErr < 0.0) CCWSpin = 0.1 - yangErr;
    // printf ("%f,%f,%f,%f\n",
    //         time,
    //         pose.angVel.x(),
    //         pose.angVel.y(),
    //         pose.angVel.z());

    // Main engines
    btScalar m1 = 0.0;
    btScalar m2 = 0.0;
    btScalar m3 = 0.0;
    btScalar m4 = 0.0;
    if (zangErr < 0.0) m1 = 0.1 - zangErr;
    if (zangErr > 0.0) m2 = 0.1 + zangErr;
    if (xangErr > 0.0) m3 = 0.1 + xangErr;
    if (xangErr < 0.0) m4 = 0.1 - xangErr;

    // ROT1 and ROT2 spin the same direction
    // ROT1 and ROT4 push the same direction
    RocketControl c;
    c.name.main1 = m1;
    c.name.main2 = m2;
    c.name.main3 = m3;
    c.name.main4 = m4;
    c.name.rot1 = CWSpin;
    c.name.rot2 = CWSpin;
    c.name.rot3 = CCWSpin;
    c.name.rot4 = CCWSpin;
    // = {0.20, 0.20, 0.20, 0.20,
    //                    CWSpin, , 0.0, 0.0};
    applyControl(c);
}

std::vector<Pose>& Rocket::getPoseHistory() {
    return poseHistory;
}

void Rocket::fireEngine(int n, btScalar throttle) {
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
    rigidBody->applyImpulse(impulse, offset);    
}

void Rocket::applyControl (const RocketControl &control) {
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

    // STRENGTHS
    engineStrength[MAIN1] = 1.0;
    engineStrength[MAIN2] = 1.0;
    engineStrength[MAIN3] = 1.0;
    engineStrength[MAIN4] = 1.0;
    engineStrength[ROT1] = 1.0; // Presumably don't have to fight gravity that much...
    engineStrength[ROT2] = 1.0;
    engineStrength[ROT3] = 1.0;
    engineStrength[ROT4] = 1.0;
}
