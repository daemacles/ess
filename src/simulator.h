#include "sensor.h"

#include <vector>

class Simulator {
    private:
        std::vector<Sensor*> sensors;
    public:
        Simulator();
        std::vector<Sensor*> getSensors();
};
