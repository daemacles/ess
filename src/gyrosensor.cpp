#include <cstdio>

#include "gyrosensor.h"
#include "entity.h"

void GyroSensor::update (double ts) {
    if (target != nullptr) {
        myData->x = target->getPose().angVel.x();
        myData->y = target->getPose().angVel.y();
        myData->z = target->getPose().angVel.z();
        myData->timestamp = target->getPose().timestamp;
    }
}
