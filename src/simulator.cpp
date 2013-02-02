#include <cstdio>
#include <vector>

#include "simulator.h"

void simCallback(btDynamicsWorld *world, btScalar timeStep) {
    Simulator *sim = static_cast<Simulator*>(world->getWorldUserInfo());
    sim->callback(timeStep);
}

Simulator::Simulator (EntityHandler *_ents):
    entities(_ents) {
    
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
    dynamicsWorld->getDispatchInfo().m_useContinuous = 0; //USE_CCD;
    dynamicsWorld->setGravity(btVector3(0, -9.8, 0));

    /// Add all entities to our dynamics world
    for (auto pr : entities->dynamicEnts) {
        auto ent = pr.second;
        if (ent->getRigidBody()) {
            dynamicsWorld->addRigidBody(ent->getRigidBody());
        }
    }

    for (auto pr : entities->staticEnts) {
        auto ent = pr.second;
        if (ent->getRigidBody()) {
            dynamicsWorld->addRigidBody(ent->getRigidBody());
        }
    }
}

void Simulator::callback (btScalar timeStep) {
    entities->callUpdates();
}

btDynamicsWorld* Simulator::getDynamicsWorld () {
    return dynamicsWorld;
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
