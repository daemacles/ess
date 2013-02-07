#ifndef _NETWORKHANDLER_H
#define _NETWORKHANDLER_H 1

#include <map>
#include <string>

#include "sensor.h"
#include "rocketcontrol.h"

class NetworkHandler {
    public:
    NetworkHandler () {}
    virtual ~NetworkHandler () {}
    
    /// Transmits sensor values
    virtual void sendSensors (const std::map<std::string, Sensor*> &sensors) = 0;

    /// Blocks to recieve a RocketControl message
    virtual RocketControl getControl () = 0;

};

#endif
