#ifndef _SENSORSERIALIZER_H
#define _SENSORSERIALIZER_H 1

#include <memory>
#include <vector>
#include <json/json.h>

#include "sensor.h"
#include "rocketcontrol.h"

class JSONSerializer {
    public:
    // SENSOR SERIALIZATION
    static std::string toJSON (const SensorData *in);

    // CONTROL SERIALIZATION
    static std::string toJSON (const RocketControl *in);
    static RocketControl* getRocketControl (const std::string &in); // on heap

    private:
    typedef std::unique_ptr<Json::Value> valPtr;
    static valPtr parse(const std::string &in);
};

#endif
