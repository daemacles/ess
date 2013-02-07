#include "pose.h"
#include <cmath>

Pose::Pose(btRigidBody *b, btScalar time)
{
    update(b, time);
    // TODO
}

void Pose::update(btRigidBody *b, btScalar time) {
    auto ori = b->getOrientation();
    worldTransform = b->getCenterOfMassTransform();
    linVel         = b->getLinearVelocity().rotate(ori.getAxis(), ori.getAngle());

    // Calculate local angular velocity
    btVector3 angVelWorld = b->getAngularVelocity();
    btVector3 xvec = btVector3(1,0,0).rotate(ori.getAxis(), ori.getAngle());
    btVector3 yvec = btVector3(0,1,0).rotate(ori.getAxis(), ori.getAngle());
    btVector3 zvec = btVector3(0,0,1).rotate(ori.getAxis(), ori.getAngle());
    angVel = {angVelWorld.dot(xvec),
              angVelWorld.dot(yvec),
              angVelWorld.dot(zvec)};
    
    // btScalar x_angle = xvec.angle(angVelWorld);
    // btScalar y_angle = yvec.angle(angVelWorld);
    // btScalar z_angle = zvec.angle(angVelWorld);
    // btScalar w = angVelWorld.length();
    // if (w == 0.0) angVel = {0,0,0};
    // else          angVel = w * btVector3(cos(x_angle), cos(y_angle), cos(z_angle));

    linForce       = b->getTotalForce().rotate(ori.getAxis(), ori.getAngle());
    torque         = b->getTotalTorque().rotate(ori.getAxis(), ori.getAngle());
    timestamp      = time;
}

