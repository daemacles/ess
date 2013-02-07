#ifndef _GYROSENSOR_H
#define _GYROSENSOR_H 1


#include "entity.h"
#include "sensor.h"

class GyroSensor : public Sensor {
    private:
    Entity *target;
    btVector3 data;
    
    public:
    /// \param _name the name of this sensor
    /// \target the entity whose angular velocity this sensor will track
    GyroSensor (std::string _name, Entity *_target):
        Sensor(_name), target(_target), data(0,0,0) {}
    
    GyroSensor (btScalar x, btScalar y, btScalar z):
        Sensor("GyroData"), target(nullptr), data(x,y,z) {}

    virtual SensorType getSensorType () const { return Sensor::GYRO; }
    virtual std::string getSensorTypeString () const { return "GYRO"; }
    virtual const btVector3& getValue () const { return data; }
    virtual btScalar getTimestamp () const { return timestamp; }
    virtual void update (btScalar ts);
};

#endif
