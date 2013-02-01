#include "simulator.h"

#include <vector>

Simulator::Simulator() {
    this->sensors.push_back(new Sensor);
    this->sensors.push_back(new Sensor);
}

std::vector<Sensor*> Simulator::getSensors() { 
    return this->sensors;
}
