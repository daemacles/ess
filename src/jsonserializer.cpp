#include <cstdio>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <json/json.h>

#include "jsonserializer.h"
#include "sensor.h"
#include "rocketcontrol.h"

// SENSOR SERIALIZATION
std::string JSONSerializer::toJSON (const SensorData *in) {
    switch(in->type) {
    case Sensor::GYRO: {
        const SensorVec3 *data = static_cast<const SensorVec3*>(in);
        const int BUFSIZE = 150;
        char buf[BUFSIZE];
        snprintf(buf, BUFSIZE,
                 "{\"class\" : \"Sensor\", \"type\":\"%s\", \"name\" : \"%s\", \"data\" : [%f, %f, %f], "
                 "\"timestamp\" : %f } ",
                 "GYRO", data->name.c_str(), data->x, data->y, data->z, data->timestamp);
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
