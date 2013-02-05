#include "entity.h"
#include "sensor.h"

class GyroSensor : public SensorVec3 {
    private:
    Entity *target;
    
    public:
    /// \param _name the name of this sensor
    /// \target the entity whose angular velocity this sensor will track
    GyroSensor (std::string _name, Entity *_target): SensorVec3(_name), target(_target) {};

    virtual const btVector3& getValue () { return target->getPose().angVel; }
    virtual btScalar getTimestamp () { return target->getPose().timestamp; }
};
