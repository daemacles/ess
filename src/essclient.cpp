#include <iostream>
#include <sstream>
#include <cstdlib>
#include <json/json.h>

#include "jsonserializer.h"
#include "sensor.h"

#include "essclient.h"

//////////////////////////////////////////////////////////////////////
// ESS CLIENT
////////////////////////////////////////////////////////////////////// 
ESSClient::ESSClient (std::string port, std::string host):
    context(1),
    socket(context, ZMQ_REP)
{
    std::stringstream hostnameStream;
    hostnameStream << "tcp://" << host << ":" << port;
    socket.connect(hostnameStream.str().c_str());
}
    
void ESSClient::registerCallback (Sensor::SensorType type, SensorCallback *cb) {
    callbacks.insert({type, cb});
}
    
bool ESSClient::getSensors() {
    SensorVec sensors;
    zmq::message_t sensorMsgs;
    socket.recv(&sensorMsgs);

    // Quit if we're told to
    std::string message((char*)sensorMsgs.data());
    if (message == "!QUIT") {
        return false;
    }
    
    Json::Value root;
    Json::Reader reader;

    // Attempt to 
    if (!reader.parse(message, root)) {
        // report to the user the failure and their locations in the document.
        std::cout << "Failed to parse message\n"
                  << reader.getFormattedErrorMessages()
                  << " : " << message
                  << std::endl;
        exit(1);
    }

    // Parse the sensors
    for (uint32_t i = 0; i != root.size(); ++i) {
        Json::Value &item = root[i];
        if (item.isString() && item.asString() == "END") {
            break;
        }

        SensorData *sensorData = nullptr;
        
        std::string type = item.get("type", "unknown").asString();
        if (type == "GYRO") {
            const Json::Value data = item["data"];
            SensorVec3 *s = new SensorVec3();
            s->type = Sensor::GYRO;
            s->x = data[0].asDouble();
            s->y = data[1].asDouble();
            s->z = data[2].asDouble();
            s->name = item["name"].asString();
            s->timestamp = item["timestamp"].asDouble();
            sensorData = s;
        }
        
        // Sensor *s = JSONSerializer::getSensor(root[i].toStyledString());
        sensors.emplace_back(sensorData);
    }

    // Execute callbacks
    for (auto &sensorp : sensors) {
        call(sensorp.get());
    }

    // Haven't seen the QUIT message yet =)
    return true;
}

void ESSClient::sendControl (RocketControl &rc) {
    // Send control values
    std::string rcString = JSONSerializer::toJSON(&rc);
    zmq::message_t controlMsg(rcString.length());
    memcpy ((void*) controlMsg.data(), rcString.c_str(), rcString.length());
    socket.send(controlMsg);
}

void ESSClient::call (SensorData *data) {
    switch (data->type) {
    case Sensor::GYRO: {
        SensorVec3 *gyroData = static_cast<SensorVec3*>(data);
        (*callbacks.at(Sensor::GYRO))(gyroData);
        break;
    }
    default:
        break;
    }
}

ESSClient::~ESSClient () {
 
}
