#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <zmq.hpp>
#include <cstdlib>
#include <json/json.h>

#include "rocketcontrol.h"
#include "jsonserializer.h"
#include "sensor.h"
#include "gyrosensor.h"

typedef std::vector<std::unique_ptr<Sensor> > SensorVec;

SensorVec getSensors(zmq::socket_t &socket) {
    SensorVec sensors;
    zmq::message_t sensorMsgs;
    socket.recv(&sensorMsgs);
        
    std::string message((char*)sensorMsgs.data());
    if (message == "!QUIT") {
        exit(0);
    }

    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(message, root)) {
        // report to the user the failure and their locations in the document.
        std::cout << "Failed to parse message\n"
                  << reader.getFormattedErrorMessages()
                  << " : " << message
                  << std::endl;
        exit(1);
    }
    
    for (int i = 0; i != root.size(); ++i) {
        Json::Value &item = root[i];
        if (item.isString() && item.asString() == "END") {
            break;
        }

        Sensor *s = nullptr;
        
        std::string type = item.get("type", "unknown").asString();
        if (type == "GYRO") {
            btScalar vals[3];
            const Json::Value data = item["data"];
            for (int i = 0; i != data.size(); ++i) {
                vals[i] = data[i].asDouble();
            }
            s = new GyroSensor(vals[0], vals[1], vals[2]);
        }
        
        // Sensor *s = JSONSerializer::getSensor(root[i].toStyledString());
        sensors.emplace_back(s);
    }

    return sensors;
}

class SensorCallback {
    public:
    virtual void operator() (GyroSensor *gyro) {};
};

class GyroCallback : public SensorCallback {
    private:
    btVector3 *data;
    
    public:
    GyroCallback (btVector3 *_data): data(_data) {}
    void operator() (GyroSensor *gyro) {
        *data = gyro->getValue();
    }
};
    

class SensorManager {
    private:
    std::map<Sensor::SensorType, SensorCallback*> callbacks;
    
    public:
    void registerCallback (Sensor::SensorType type, SensorCallback *cb) {
        callbacks.insert({type, cb});
    }
    
    void call (Sensor *sensor) {
        switch (sensor->getSensorType()) {
        case Sensor::GYRO: {
            GyroSensor *gyro = static_cast<GyroSensor*>(sensor);
            (*callbacks.at(Sensor::GYRO))(gyro);
            break;
        }
        default:
            break;
        }
    }
};

int main(int argc, char **argv) {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);

    socket.connect("tcp://localhost:51919");

    btVector3 gyroData;
    GyroCallback gyroCb(&gyroData);
    SensorManager sensorManager;
    sensorManager.registerCallback(Sensor::GYRO, &gyroCb);

    bool running = true;
    while (running) {
        // Get sensor messages
        SensorVec sensors = getSensors(socket);
        for (auto &sensorp : sensors) {
            sensorManager.call(sensorp.get());
        }
        // std::cout << "Received " << message << std::endl;
        
        // No spinning! (a controller)
        RocketControl rc = {0,0,0,0,0,0,0,0};

        btScalar xangErr = gyroData.x();
        btScalar yangErr = gyroData.y();
        btScalar zangErr = gyroData.z();

        // Rotation engines
        btScalar CWSpin = 0.0;
        btScalar CCWSpin = 0.0;
        if (yangErr > 0.0) CWSpin  = 1;//0.2 + 10*yangErr;
        if (yangErr < 0.0) CCWSpin = 1;//0.2 - 10*yangErr;
        // printf ("%f,%f,%f,%f\n",
        //         time,
        //         pose.angVel.x(),
        //         pose.angVel.y(),
        //         pose.angVel.z());

        // Main engines
        btScalar m1 = 0.0;
        btScalar m2 = 0.0;
        btScalar m3 = 0.0;
        btScalar m4 = 0.0;
        if (zangErr < 0.0) m1 = 0.2 - 10*zangErr;
        if (zangErr > 0.0) m2 = 0.2 + 10*zangErr;
        if (xangErr > 0.0) m3 = 0.2 + 10*xangErr;
        if (xangErr < 0.0) m4 = 0.2 - 10*xangErr;

        // ROT1 and ROT2 spin the same direction
        // ROT1 and ROT4 push the same direction
        rc.name.main1 = m1;
        rc.name.main2 = m2;
        rc.name.main3 = m3;
        rc.name.main4 = m4;
        rc.name.rot1 = CWSpin;
        rc.name.rot2 = CWSpin;
        rc.name.rot3 = CCWSpin;
        rc.name.rot4 = CCWSpin;

        // Send control values
        std::string rcString = JSONSerializer::toJSON(&rc);
        zmq::message_t controlMsg(rcString.length());
        memcpy ((void*) controlMsg.data(), rcString.c_str(), rcString.length());
        socket.send(controlMsg);
    }
    
    return 0;
}
