#ifndef _ENTITYHANDLER_H
#define _ENTITYHANDLER_H

#include <map>
#include <string>
#include <mutex>
#include "btBulletDynamicsCommon.h"

#include "entity.h"
#include "rocket.h"
#include "sensor.h"

class EntityHandler {
    private:
    std::mutex updateMutex;

    public:
    typedef std::map<std::string, Entity*> entityMap_t;
    entityMap_t dynamicEnts;
    entityMap_t staticEnts;
    std::map<std::string, Sensor*> sensors;
    Rocket *rocket;

    EntityHandler ();
    virtual ~EntityHandler ();

    void init ();

    void lock () { updateMutex.lock(); }
    void unlock () { updateMutex.unlock(); }
    
    void addDynamic (std::string name, Entity* e) { dynamicEnts[name] = e; }
    void addStatic  (std::string name, Entity* e) { staticEnts[name] = e; }
    void addSensor  (std::string name, Sensor* e) { sensors[name] = e; }

    void callUpdates (btScalar delta_t, btScalar time);
};

#endif
