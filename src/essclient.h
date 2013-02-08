#ifndef _ESSCLIENT_H
#define _ESSCLIENT_H 1

#include <vector>
#include <memory>
#include <map>
#include <string>
#include <zmq.hpp>

#include "rocketcontrol.h"
#include "sensor.h"
#include "gyrosensor.h"

//////////////////////////////////////////////////////////////////////
// SENSOR CALLBACK
////////////////////////////////////////////////////////////////////// 
class SensorCallback {
    public:
    // Define a virtual function for each sensor type
    virtual void operator() (GyroSensor *gyro) {};
};    

//////////////////////////////////////////////////////////////////////
// ESS CLIENT
////////////////////////////////////////////////////////////////////// 
class ESSClient {
    public:
    typedef std::vector<std::unique_ptr<Sensor> > SensorVec;
    
    private:
    zmq::context_t context;
    zmq::socket_t socket;
    std::map<Sensor::SensorType, SensorCallback*> callbacks;

    public:
    // The constructor automatically tries to connect to the server.  This is
    // ok if the server is not yet running because ZMQ will wait for it.
    ESSClient (std::string port="1200", std::string host="localhost");
    ~ESSClient ();

    void registerCallback (Sensor::SensorType type, SensorCallback *cb);

    // Blocks, waits for the server to send a list of sensor readings.  For
    // each sensor reading, it invokes the callback associated with that
    // sensor type.
    bool getSensors();

    // Sends a control message to the server.
    void sendControl (RocketControl &rc);

    private:
    void call (Sensor *sensor);
};

#endif
