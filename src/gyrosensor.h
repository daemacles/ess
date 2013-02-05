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
        Sensor(_name), target(_target) {};

    virtual SensorType getSensorType () { return Sensor::GYRO; }
    virtual const btVector3& getValue () { return data; }
    virtual btScalar getTimestamp () { return timestamp; }
    virtual void update (btScalar ts);
};
