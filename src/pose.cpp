#include "pose.h"

Pose::Pose(btRigidBody *b, btScalar time):
    worldTransform(b->getCenterOfMassTransform()),
    linVel(b->getLinearVelocity()),
    angVel(b->getAngularVelocity()),
    linForce(b->getTotalForce()),
    torque(b->getTotalTorque()),
    timestamp(time)
{
    // TODO
}

void Pose::update(btRigidBody *b, btScalar time) {
    worldTransform = b->getCenterOfMassTransform();
    linVel         = b->getLinearVelocity();
    angVel         = b->getAngularVelocity();
    linForce       = b->getTotalForce();
    torque         = b->getTotalTorque();
    timestamp      = time;
}

