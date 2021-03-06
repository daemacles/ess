#include <iostream>

#include "simulator.h"
#include "zmqhandler.h"

void simCallback(btDynamicsWorld *world, btScalar timeStep) {
    Simulator *sim = static_cast<Simulator*>(world->getWorldUserInfo());
    sim->callback(timeStep);
}

Simulator::Simulator (EntityHandler *_ents, NetworkHandler *_net):
    entities(_ents),
    networkHandler(_net),
    elapsedTime(0.0),
    running(false),
    simThread(nullptr)
{
    // Create a default network handler if one wasn't passed to us.
    if (_net == nullptr) {
        networkHandler = new ZMQHandler();
    }
    
    /// collision configuration contains default setup for memory, collision setup
    collisionConfiguration = new btDefaultCollisionConfiguration();

    /// use the default collision dispatcher. For parallel processing you can
    /// use a diffent dispatcher (see Extras/BulletMultiThreaded)
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    dispatcher->registerCollisionCreateFunc(BOX_SHAPE_PROXYTYPE, BOX_SHAPE_PROXYTYPE,
         collisionConfiguration->getCollisionAlgorithmCreateFunc(CONVEX_SHAPE_PROXYTYPE,
                                                                 CONVEX_SHAPE_PROXYTYPE));

    broadphase = new btDbvtBroadphase();

    /// the default constraint solver. For parallel processing you can use a
    /// different solver (see Extras/BulletMultiThreaded)
    btSequentialImpulseConstraintSolver* sol = new btSequentialImpulseConstraintSolver();
    solver = sol;

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase,
                                                solver, collisionConfiguration);
    dynamicsWorld->getSolverInfo().m_splitImpulse = true;
    dynamicsWorld->getSolverInfo().m_numIterations = 20;
    dynamicsWorld->getDispatchInfo().m_useContinuous = 1;
    dynamicsWorld->setGravity(btVector3(0, -9.8, 0));

    // Hook up our callback
    dynamicsWorld->setInternalTickCallback(simCallback, static_cast<void*>(this));
    

    // Add all entities to our dynamics world, starting with the static
    // things.
    for (auto pr : entities->staticEnts) {
        auto ent = pr.second;
        if (ent->getRigidBody()) {
            // std::cout << "Adding static entity " << pr.first << std::endl;
            dynamicsWorld->addRigidBody(ent->getRigidBody());
        }
    }
    
    for (auto pr : entities->dynamicEnts) {
        auto ent = pr.second;
        if (ent->getRigidBody()) {
            // std::cout << "Adding dynamic entity " << pr.first << std::endl;
            dynamicsWorld->addRigidBody(ent->getRigidBody());
        }
    }
}

void Simulator::start () {
    if (!running) {
        running = true;
        simThread = new std::thread(&Simulator::mainLoop, this);
    }
}

void Simulator::stop() {
    if (running) {
        running = false;
        simThread->join();
        delete simThread;
        simThread = nullptr;
    }
}

void Simulator::stepSimulation (btScalar delta_t) {
    entities->lock();
    dynamicsWorld->stepSimulation(delta_t);
    entities->unlock();
}


void Simulator::callback (btScalar delta_t) {
    elapsedTime += delta_t;
    entities->callUpdates(delta_t, elapsedTime);
}

btDynamicsWorld* Simulator::getDynamicsWorld () {
    return dynamicsWorld;
}

RocketControl Simulator::getControl () {
    return networkHandler->getControl();
}

void Simulator::sendSensors () {
    networkHandler->sendSensors(entities->sensors);
}


void Simulator::mainLoop (void) {
    // TODO: change duration so it limits to 100 updates a second, but allows
    // for slower times if the client really has to think about things.
    std::cout << "Mainloop running" << std::endl;
    while (running) {
        sendSensors();
        nextControl = getControl();
        entities->rocket->applyControl(nextControl);
        stepSimulation(1./100);

        // Rate limit the simulation
        std::chrono::milliseconds dura(10);
        std::this_thread::sleep_for(dura);
    }
    std::cout << "Mainloop not running" << std::endl;
}

Simulator::~Simulator () {
    // remove the rigidbodies from the dynamics world
    for (int i = dynamicsWorld->getNumCollisionObjects()-1; i != 0 ; --i) {
        btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
        dynamicsWorld->removeCollisionObject( obj );
    }

    delete dynamicsWorld;
    delete solver;
    delete broadphase;
    delete dispatcher;
    delete collisionConfiguration;
}

