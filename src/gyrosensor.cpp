#include <cstdio>

#include "gyrosensor.h"

void GyroSensor::update (btScalar ts) {
    if (target != nullptr) {
        data = target->getPose().angVel;
        timestamp = target->getPose().timestamp;
        // auto &angvel = getValue();
        // printf ("%9.4f %8.3f %8.3f %8.3f\n", getTimestamp(), angvel.x(), angvel.y(), angvel.z());
    }
}
