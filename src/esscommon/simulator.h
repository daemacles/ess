#ifndef _SIMULATOR_H
#define _SIMULATOR_H 1

#include <thread>
#include <chrono>
#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h"

#include "entityhandler.h"
#include "networkhandler.h"
#include "rocket.h"
#include "rocketcontrol.h"

void simCallback(btDynamicsWorld *world, btScalar timeStep);

class Simulator {
    protected:
    // The memory for these two handlers is not managed by Simulator
    EntityHandler                   *entities;
    NetworkHandler                  *networkHandler;
    
    btDynamicsWorld                 *dynamicsWorld;
    btDefaultCollisionConfiguration *collisionConfiguration;
    btCollisionDispatcher           *dispatcher;
    btBroadphaseInterface           *broadphase;
    btConstraintSolver              *solver;
    btScalar                         elapsedTime; // time since the beginning
    bool                             running;     // should the simulator thread run?
    std::thread                     *simThread;   // thread in which mainLoop runs
    RocketControl                    nextControl;
    
    public:
    Simulator (EntityHandler *_ents, NetworkHandler *_net = nullptr);
    virtual ~Simulator ();

    void start ();
    void stop ();
    void stepSimulation (btScalar delta_t);
    void callback (btScalar delta_t);
    btDynamicsWorld* getDynamicsWorld ();

    RocketControl getControl ();
    void sendSensors ();

    // The function for a thread started by 'start()' that repeatedly calls:
    // 1) getControl
    // 2) stepSimulation
    // 3) sendSensors
    void mainLoop (void);

    private:
};

#endif
