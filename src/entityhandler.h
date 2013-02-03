#ifndef _ENTITYHANDLER_H
#define _ENTITYHANDLER_H

#include <map>
#include <string>
#include "btBulletDynamicsCommon.h"

#include "entity.h"
#include "sensor.h"

class EntityHandler {
    private:

    public:
    typedef std::map<std::string, Entity*> entityMap_t;
    entityMap_t dynamicEnts;
    entityMap_t staticEnts;
    std::map<std::string, Sensor*> sensors;

    EntityHandler ();
    virtual ~EntityHandler ();

    void init ();
    
    void addDynamic (std::string name, Entity* e) { dynamicEnts[name] = e; }
    void addStatic  (std::string name, Entity* e) { staticEnts[name] = e; }
    void addSensor  (std::string name, Sensor* e) { sensors[name] = e; }

    void callUpdates (btScalar timeStep, btScalar time);
};

#endif
