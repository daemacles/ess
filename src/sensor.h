#ifndef _SENSOR_H
#define _SENSOR_H

#include <string>

#include "btBulletDynamicsCommon.h"

class Sensor {
    private:
    

    public:
    float getValue();
    std::string getName();
};

#endif
