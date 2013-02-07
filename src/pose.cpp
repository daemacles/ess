#include "pose.h"
#include <cmath>

Pose::Pose(btRigidBody *b, btScalar time)
{
    update(b, time);
    // TODO
}

void Pose::update(btRigidBody *b, btScalar time) {
    // The orientation is used to change from the world frame of reference to
    // our local frame of referene.
    auto ori = b->getOrientation();

    worldTransform = b->getCenterOfMassTransform();
    linVel         = b->getLinearVelocity().rotate(ori.getAxis(), ori.getAngle());
    linForce       = b->getTotalForce().rotate(ori.getAxis(), ori.getAngle());

    // IS THIS IN WORLD COORDS SOMEHOW???
    torque         = b->getTotalTorque().rotate(ori.getAxis(), ori.getAngle());

    // Calculate local angular velocity
    btVector3 angVelWorld = b->getAngularVelocity();
    btVector3 xvec = btVector3(1,0,0).rotate(ori.getAxis(), ori.getAngle());
    btVector3 yvec = btVector3(0,1,0).rotate(ori.getAxis(), ori.getAngle());
    btVector3 zvec = btVector3(0,0,1).rotate(ori.getAxis(), ori.getAngle());
    angVel = {angVelWorld.dot(xvec),
              angVelWorld.dot(yvec),
              angVelWorld.dot(zvec)};

    // Keep time
    timestamp      = time;
}

