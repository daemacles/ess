#ifndef _SENSOR_H
#define _SENSOR_H

#include <string>
#include "btBulletDynamicsCommon.h"

#include "pose.h"

class Sensor {
    // -- ATTRIBUTES --
    protected:
    std::string name;
    btScalar timestamp;
    
    public:
    enum SensorType {
        GYRO,
        ACCELEROMETER,
        HEIGHT,
        DISTANCE,
        RANGEFINDER
    };

    // -- FUNCTIONS --
    protected:
    
    public:
    Sensor (std::string _name): name(_name) {}
    
    std::string getName () { return name; }

    // Subclassed sensors define this to return the type that their getValue
    // method uses so that they can be static_cast as needed.
    virtual SensorType getSensorType () = 0;
    virtual std::string getSensorTypeString () = 0;

    // Returns the time that this sensor value was taken
    virtual btScalar getTimestamp () = 0;

    // Updates the sensor after a step in the dynamics world
    virtual void update (btScalar ts) = 0;
};

#endif
