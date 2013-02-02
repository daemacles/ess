#include "pose.h"

Pose::Pose(btRigidBody *b): worldTransform(b->getCenterOfMassTransform()),
                            linVel(b->getLinearVelocity()),
                            angVel(b->getAngularVelocity()),
                            linForce(b->getTotalForce()),
                            torque(b->getTotalTorque()) {
    // TODO
}

