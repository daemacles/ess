#include <cstdio>

#include "gyrosensor.h"

void GyroSensor::update (btScalar ts) {
    if (target != nullptr) {
        data.x = target->getPose().angVel.x();
        data.y = target->getPose().angVel.y();
        data.z = target->getPose().angVel.z();
        timestamp = target->getPose().timestamp;
        // auto &angvel = getValue();
        // printf ("%9.4f %8.3f %8.3f %8.3f\n", getTimestamp(), angvel.x(), angvel.y(), angvel.z());
    }
}
