#ifndef _SENSOR_H
#define _SENSOR_H

#include <string>

class SensorData;
    
class Sensor {
    // -- ATTRIBUTES --
    protected:
    std::string name;
    SensorData *data;
    
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
    
    std::string getName () const { return name; }

    virtual SensorData* getData() { return data; }

    // Updates the sensor after a step in the dynamics world
    virtual void update (double ts) = 0;
};

struct SensorData {
    std::string name;
    double timestamp;
    Sensor::SensorType type;
};

struct SensorVec3 : SensorData {
    double x, y, z;
};


#endif
