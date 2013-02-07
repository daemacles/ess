#include <iostream>
#include <string>
#include <memory>
#include <zmq.hpp>

#include "rocketcontrol.h"
#include "jsonserializer.h"
#include "sensor.h"
#include "gyrosensor.h"

int main(int argc, char **argv) {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);

    socket.connect("tcp://localhost:51919");

    bool running = true;
    while (running) {
        // Get sensor messages
        zmq::message_t sensorMsg;
        socket.recv(&sensorMsg);
        
        std::string message((char*)sensorMsg.data());
        if (message == "!QUIT") {
            running = false;
            break;
        }
        // std::cout << "Received " << message << std::endl;
        
        RocketControl rc = {0,0,0,0,0,0,0,0};
        std::unique_ptr<Sensor> sensor(JSONSerializer::getSensor(message));
        if (sensor->getSensorType() == Sensor::GYRO) {
            GyroSensor *gs = static_cast<GyroSensor*>(sensor.get());
            btVector3 gyroData = gs->getValue();

            // No spinning! (a controller)
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
            // = {0.20, 0.20, 0.20, 0.20,
            //                    CWSpin, , 0.0, 0.0};        
            
        }
        

        // Send control values
        std::string rcString = JSONSerializer::toJSON(&rc);
        std::cout << rcString << std::endl;
        zmq::message_t controlMsg(rcString.length());
        memcpy ((void*) controlMsg.data(), rcString.c_str(), rcString.length());
        socket.send(controlMsg);
    }
    
    return 0;
}
