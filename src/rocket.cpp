#include "rocket.h"

Rocket::Rocket (btVector3 startPos, btScalar mass) {
    ShapeHandler *sh = ShapeHandler::getHandler();
    if (!sh->hasShape("rocket01")) {
        // Load in the shapes to be used
        // sh->addMesh("rocket01", "../models/rocket01.stl", true);
        sh->addConvexHull("rocket01", "../models/rocket01.stl");
    }
    
    btCollisionShape *rocketShape = sh->getShape("rocket01");
    this->openglObject = sh->getMesh("rocket01")->openglobj;

    // Set up our beginning transform
    //btQuaternion rot(0,0,0,1);
    btTransform trans;
    trans.setIdentity();
    trans.setOrigin(startPos);
  
    initRigidBody(mass, rocketShape, trans);
}
    
void Rocket::update (btScalar timeStep, btScalar time) {
    // First, save our current (old) pose
    poseHistory.push_back(pose);

    // Next parent's update, which will update our pose
    Entity::update(timeStep, time);   

    // Bouncing rocket
    float height = -7.0f;
    float maxThrust = 20.0f;
    rigidBody->setActivationState(ACTIVE_TAG);
    auto ori = rigidBody->getOrientation();
    auto trans = rigidBody->getWorldTransform().getOrigin();
    float error = height - trans[1];
    if (error < 0) error = 0.0f;
    float impulseStrength = 5.0f * error;
    if (impulseStrength > maxThrust) impulseStrength = maxThrust;
    btVector3 thrust(0,1,0);
    btVector3 impulse = thrust.rotate(ori.getAxis(), ori.getAngle());
    impulse *= impulseStrength;
    btVector3 relPos(0,0,0);
    //rigidBody->applyImpulse(impulse,relPos);    
}

std::vector<Pose>& Rocket::getPoseHistory() {
    return poseHistory;
}
