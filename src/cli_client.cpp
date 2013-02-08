#include <cstdio>

#include "essclient.h"

SensorVec3 gyroData;            // Global variable for gyro data

class GyroCallback : public SensorCallback {
    public:
    void operator() (SensorVec3 *data) {
        gyroData = *data;
    }
};

RocketControl generateControl ();

int main(int argc, char **argv) {
    if (argc != 2) exit(1);

    ESSClient client(argv[1]);

    GyroCallback gcb;
    client.registerCallback(Sensor::GYRO, &gcb);

    bool running = true;
    while (running) {
        // Get sensor messages
        running = client.getSensors();

        // Determine next control settings
        RocketControl rc = generateControl();

        // Send the control message
        client.sendControl(rc);
    }
        
    return 0;
}

RocketControl generateControl () {
    // No spinning! (a controller)
    RocketControl rc{};

    float xangErr = gyroData.x;
    float yangErr = gyroData.y;
    float zangErr = gyroData.z;

    // Rotation engines
    float CWSpin = 0.0;
    float CCWSpin = 0.0;
    if (yangErr > 0.0) CWSpin  = 1;//0.2 + 10*yangErr;
    if (yangErr < 0.0) CCWSpin = 1;//0.2 - 10*yangErr;

    // Main engines
    float m1 = 0.0;
    float m2 = 0.0;
    float m3 = 0.0;
    float m4 = 0.0;
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

    return rc;
}
