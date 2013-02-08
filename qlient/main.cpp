#include <QApplication>
#include <thread>
#include <memory>
#include <string>

#include "qtessclient.h"
#include "essclient.h"

SensorVec3 gyroData;            // Global variable for gyro data
bool qtRunning;
RocketControl rc;

class GyroCallback : public SensorCallback {
    public:
    void operator() (SensorVec3 *data) {
        gyroData = *data;
    }
};

RocketControl generateControl () {
//    RocketControl rc = {0,0,0,0,0,0,0,0};
//    rc.name.main1 = .25;
//    rc.name.main2 = .25;
//    rc.name.main3 = .25;
//    rc.name.main4 = .25;
    return rc;
}

int clientThreadFn() {
    ESSClient client("1200");

    GyroCallback gcb;
    client.registerCallback(Sensor::GYRO, &gcb);

    bool running = true;
    while (running && qtRunning) {
        // Get sensor messages
        running = client.getSensors();

        // Determine next control settings
        //RocketControl rc = generateControl();

        // Send the control message
        client.sendControl(rc);
    }

    return 0;
}


int main(int argc, char *argv[])
{
    qtRunning = true;
    std::thread t1(clientThreadFn);
    QApplication a(argc, argv);
    QtESSClient w(&qtRunning);
    w.show();
    
    bool success = a.exec();

    t1.join();

    return success;
}
