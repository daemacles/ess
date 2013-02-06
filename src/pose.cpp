#include "pose.h"

Pose::Pose(btRigidBody *b, btScalar time)
{
    update(b, time);
    // TODO
}

void Pose::update(btRigidBody *b, btScalar time) {
    auto ori = b->getOrientation();
    worldTransform = b->getCenterOfMassTransform();
    linVel         = b->getLinearVelocity().rotate(ori.getAxis(), ori.getAngle());
    angVel         = b->getAngularVelocity().rotate(ori.getAxis(), ori.getAngle());
    // angVel         = b->getAngularVelocity();
    linForce       = b->getTotalForce().rotate(ori.getAxis(), ori.getAngle());
    torque         = b->getTotalTorque().rotate(ori.getAxis(), ori.getAngle());
    timestamp      = time;
}

