#include "essclient.h"

class GyroCallback : public SensorCallback {
    private:
    btVector3 *data;
    
    public:
    GyroCallback (btVector3 *_data): data(_data) {}
    void operator() (GyroSensor *gyro) {
        *data = gyro->getValue();
    }
};

int main(int argc, char **argv) {
    if (argc != 2) exit(1);
    
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);

    char buf[80];
    snprintf(buf, 80, "tcp://localhost:%s", argv[1]);
    socket.connect(buf);

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

        //printf("%9.4f %9.4f %9.4f\n", gyroData.x(), gyroData.y(), gyroData.z());
        
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
