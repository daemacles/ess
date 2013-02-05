#ifndef _SENSOR_H
#define _SENSOR_H

#include <string>
#include "btBulletDynamicsCommon.h"

#include "pose.h"

class Sensor {
    // -- ATTRIBUTES --
    protected:
    std::string name;
    
    public:
    enum SensorDataType {
        VECTOR3,
        SCALAR
    };

    // -- FUNCTIONS --
    protected:
    
    public:
    Sensor (std::string _name): name(_name) {}
    
    std::string getName () { return name; }

    // Subclassed sensors define this to return the type that their getValue
    // method uses so that they can be static_cast as needed.
    virtual SensorDataType getDataType () = 0;

    // Returns the time that this sensor value was taken
    virtual btScalar getTimestamp () = 0;
};

class SensorVec3 : public Sensor {
    public:
    SensorVec3 (std::string _name) : Sensor(_name) {};
    virtual SensorDataType getDataType () { return VECTOR3; }
    virtual const btVector3& getValue() = 0;
    virtual btScalar getTimestamp () = 0;
};
#endif
