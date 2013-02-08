#ifndef _GYROSENSOR_H
#define _GYROSENSOR_H 1

#include "sensor.h"

class Entity;

class GyroSensor : public Sensor {
    private:
    Entity *target;
    SensorVec3 *myData;
    
    public:
    /// \param _name the name of this sensor
    /// \target the entity whose angular velocity this sensor will track
    GyroSensor (std::string _name, Entity *_target):
        Sensor(_name), target(_target), myData(new SensorVec3())
    {
        myData->x = 0; myData->y = 0; myData->z = 0;
        myData->name = name;
        data = myData;
    }
    
    GyroSensor (double x, double y, double z):
        Sensor("Gyro"), target(nullptr), myData(new SensorVec3())
    {
        myData->x = x; myData->y = y; myData->z = z;
        myData->name = name;
        data = myData;
    }

    ~GyroSensor () {
        delete myData;
        myData = nullptr;
        data = nullptr;
    }

    virtual void update (double ts);
};

#endif
