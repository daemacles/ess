#ifndef _ZMQHANDER_H
#define _ZMQHANDER_H 1

#include <zmq.hpp>
#include <cstdio>

#include "networkhandler.h"

class ZMQHandler : public NetworkHandler {
    protected:
    zmq::context_t context;
    zmq::socket_t  socket;

    public:
    ZMQHandler (int socketNum = 51919); // E=5th, S=19th letters in alphabet =)
    virtual ~ZMQHandler ();
    
    /// Transmits sensor values
    virtual void sendSensors (const std::map<std::string, Sensor*> &sensors);

    /// Blocks to recieve a RocketControl message
    virtual RocketControl getControl ();
    

};

#endif
