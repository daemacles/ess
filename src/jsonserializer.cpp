#include <cstdio>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <json/json.h>
#include "btBulletDynamicsCommon.h"

#include "jsonserializer.h"
#include "sensor.h"
#include "gyrosensor.h"
#include "rocketcontrol.h"

// SENSOR SERIALIZATION
std::string JSONSerializer::toJSON (Sensor const *in) {
    switch(in->getSensorType()) {
    case Sensor::GYRO: {
        GyroSensor const *gs = static_cast<const GyroSensor*>(in);
        SensorVec3 data = gs->getValue();
        const int BUFSIZE = 120;
        char buf[BUFSIZE];
        snprintf(buf, BUFSIZE,
                 "{\"class\" : \"Sensor\", \"type\":\"%s\", \"name\" : \"%s\", \"data\" : [%f, %f, %f]}",
                 gs->getSensorTypeString().c_str(), gs->getName().c_str(),
                 data.x, data.y, data.z);
        return std::string(buf);
        break;
    }

    default: {
        printf("ERROR! Unknown Sensor Type: %s\n", __func__);
        exit(1);
        break;
    }
    }
}

Sensor* JSONSerializer::getSensor (const std::string &in) {
    valPtr rootp = parse(in);
    Sensor *sensor = nullptr;

    std::string type = rootp->get("type", "unknown").asString();
    if (type == "GYRO") {
        btScalar vals[3];
        const Json::Value data = (*rootp)["data"];
        for (uint32_t i = 0; i != data.size(); ++i) {
            vals[i] = data[i].asDouble();
        }
        sensor = new GyroSensor(vals[0], vals[1], vals[2]);
    }

    return sensor;
}

// CONTROL SERIALIZATION
std::string JSONSerializer::toJSON (const RocketControl *in) {
    std::stringstream ss (std::stringstream::in | std::stringstream::out);
    ss << "{\"class\" : \"Control\", \"type\" : \"RocketControl\", \"data\" : [";
    for (int i = 0; i != RocketControl::NUM_ENGINES-1; ++i) {
        ss << in->engine[i] << ", ";
    }
    ss << in->engine[RocketControl::NUM_ENGINES-1] << "]}";
    return ss.str();
}

RocketControl* JSONSerializer::getRocketControl (const std::string &in) {
    valPtr rootp = parse(in);
    RocketControl *rc = new RocketControl();

    std::string type = rootp->get("type", "unknown").asString();
    if (type != "RocketControl") {
        exit(1);
    }

    const Json::Value data = (*rootp)["data"];
    for (uint32_t i = 0; i != data.size(); ++i) {
        rc->engine[i] = data[i].asDouble();
    }
    
    return rc;
}

JSONSerializer::valPtr JSONSerializer::parse (const std::string &in) {
    Json::Value *root = new Json::Value();
    Json::Reader reader;
    if (!reader.parse(in, *root)) {
        // report to the user the failure and their locations in the document.
        std::cout << "Failed to parse message\n"
                  << reader.getFormattedErrorMessages()
                  << " : " << in
                  << std::endl;
        exit(1);
    }

    return valPtr(root);
}    
