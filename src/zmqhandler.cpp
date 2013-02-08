#include <cstdio>
#include <memory>
#include <sstream>
#include <string>

#include "zmqhandler.h"
#include "jsonserializer.h"

ZMQHandler::ZMQHandler (int socketNum):
    context(1),
    socket(context, ZMQ_REQ)    // must do send then recv, repeating
{
    // Suffer fools not
    if (socketNum > 60000 or socketNum < 1024) {
        exit(1);
    }

    const unsigned int BUFSIZE=40;
    char bindAddr[BUFSIZE];
    snprintf(bindAddr, BUFSIZE, "tcp://*:%d", socketNum);
    socket.bind(bindAddr);
}

void ZMQHandler::sendSensors (const std::map<std::string, Sensor*> &sensors) {
    std::stringstream ss;
    ss << "[";
    for (auto pr : sensors) {
        Sensor *sensor = pr.second;
        std::string sensorString = JSONSerializer::toJSON(sensor);
        ss << sensorString << ", ";
    }
    ss << "\"END\"]";
    std::string msgString = ss.str();
    zmq::message_t sensorMsg(msgString.length());
    memcpy((void*)sensorMsg.data(), msgString.c_str(), msgString.length());
    socket.send(sensorMsg);
}

RocketControl ZMQHandler::getControl (void) {
    zmq::message_t controlMsg;

    // Wait for next message
    socket.recv (&controlMsg);
    std::string rawString((char*)controlMsg.data());

    std::unique_ptr<RocketControl> rc(JSONSerializer::getRocketControl(rawString));
    return *rc;
}

ZMQHandler::~ZMQHandler () {
    zmq::message_t quitMsg(5);
    memcpy ((void*)quitMsg.data(), "!QUIT", 5);
    socket.send(quitMsg);
}

