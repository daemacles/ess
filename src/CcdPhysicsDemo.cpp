/*
  Bullet Continuous Collision Detection and Physics Library
  Copyright (c) 2003-2006 Erwin Coumans  http://continuousphysics.com/Bullet/

  This software is provided 'as-is', without any express or implied warranty.
  In no event will the authors be held liable for any damages arising from the
  use of this software.  Permission is granted to anyone to use this software
  for any purpose, including commercial applications, and to alter it and
  redistribute it freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
  claim that you wrote the original software. If you use this software in a
  product, an acknowledgment in the product documentation would be appreciated
  but is not required.  2. Altered source versions must be plainly marked as
  such, and must not be misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include <stdio.h> // printf debugging
#include <btBulletDynamicsCommon.h> // main Bullet include file, contains most
                                    // common include files.

#include <BulletCollision/Gimpact/btGImpactShape.h>

#include "CcdPhysicsDemo.h"
#include "GlutStuff.h"
#include "GLDebugFont.h"
#include "GLDebugDrawer.h"

#define CUBE_HALF_EXTENTS 0.5
#define EXTRA_HEIGHT 1.f

static GLDebugDrawer sDebugDrawer;

CcdPhysicsDemo::CcdPhysicsDemo() :
    m_rocketMesh(nullptr),
    m_ccdMode(USE_CCD)
{
    setDebugMode(btIDebugDraw::DBG_DrawText + btIDebugDraw::DBG_NoHelpText);
    setCameraDistance(btScalar(20.));
}

void CcdPhysicsDemo::clientMoveAndDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    // simple dynamics world doesn't handle fixed-time-stepping
    //float ms = getDeltaTimeMicroseconds();
 
    /// step the simulation
    if (m_dynamicsWorld) {
        m_dynamicsWorld->stepSimulation(1./60.);// ms / 1000000.f);
        // optional but useful: debug drawing
        m_dynamicsWorld->debugDrawWorld();
    }
  
    renderme(); 
    displayText();
    glFlush();
    swapBuffers();
}

void myCallback(btDynamicsWorld *world, btScalar timeStep) {
    CcdPhysicsDemo *d = static_cast<CcdPhysicsDemo *>(world->getWorldUserInfo());
    d->callback(timeStep);
}
void CcdPhysicsDemo::callback(btScalar timeStep) {
    // Bouncing rocket
    float height = 5.0f;
    float maxThrust = 20.0f;
    m_rocket->setActivationState(ACTIVE_TAG);
    auto ori = m_rocket->getOrientation();
    auto trans = m_rocket->getWorldTransform().getOrigin();
    float error = height - trans[1];
    if (error < 0) error = 0.0f;
    float impulseStrength = 5.0f * error;
    if (impulseStrength > maxThrust) impulseStrength = maxThrust;
    btVector3 thrust(0,1,0);
    btVector3 impulse = thrust.rotate(ori.getAxis(), ori.getAngle());
    impulse *= impulseStrength;
    btVector3 relPos(0,0,0);
    m_rocket->applyImpulse(impulse,relPos);
}


void CcdPhysicsDemo::displayText() {
    int lineWidth = 440;
    int xStart = m_glutScreenWidth - lineWidth;
    int yStart = 20;

    if((getDebugMode() & btIDebugDraw::DBG_DrawText)!=0) {
        setOrthographicProjection();
        glDisable(GL_LIGHTING);
        glColor3f(0, 0, 0);
        char buf[124];
  
        glRasterPos3f(xStart, yStart, 0);
        switch (m_ccdMode) {
        case USE_CCD: {
            sprintf(buf,"Predictive contacts and motion clamping");
            break;
        }
        case USE_NO_CCD: {
            sprintf(buf,"CCD handling disabled");
            break;
        }
        default: {
            sprintf(buf,"unknown CCD setting");
        };
        };
        GLDebugDrawString(xStart, yStart, buf);

        yStart += 20;
        glRasterPos3f(xStart, yStart, 0);
        sprintf(buf,"Press 'p' to change CCD mode");
        GLDebugDrawString(xStart,yStart,buf);

        if (m_rocket) {
            yStart += 20;
            glRasterPos3f(xStart, yStart, 0);
            auto ori = m_rocket->getOrientation();
            auto axis = ori.getAxis();
            auto angle = ori.getAngle();
            sprintf(buf, "Orientation: (%2.2f, %2.2f, %2.2f) %2.2f", axis.x(), axis.y(), axis.z(),
                    angle);
            GLDebugDrawString(xStart, yStart, buf);
        }
  
        resetPerspectiveProjection();
        glEnable(GL_LIGHTING);
    } 
}

void CcdPhysicsDemo::displayCallback(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    renderme();
    displayText();

    // optional but useful: debug drawing to detect problems
    if (m_dynamicsWorld) {
        m_dynamicsWorld->debugDrawWorld();
    }

    glFlush();
    swapBuffers();
}

void CcdPhysicsDemo::setDynamicsWorld (btDynamicsWorld *world) {
    m_dynamicsWorld = world;
}

void CcdPhysicsDemo::initPhysics() {
    setTexturing(true);
    setShadows(true);
 
    m_ShootBoxInitialSpeed = 80.f;

    // /// collision configuration contains default setup for memory, collision setup
    // m_collisionConfiguration = new btDefaultCollisionConfiguration();

    // /// use the default collision dispatcher. For parallel processing you can
    // /// use a diffent dispatcher (see Extras/BulletMultiThreaded)
    // m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
    // m_dispatcher->registerCollisionCreateFunc(BOX_SHAPE_PROXYTYPE, BOX_SHAPE_PROXYTYPE,
    //      m_collisionConfiguration->getCollisionAlgorithmCreateFunc(CONVEX_SHAPE_PROXYTYPE,
    //                                                                CONVEX_SHAPE_PROXYTYPE));

    // m_broadphase = new btDbvtBroadphase();

    // /// the default constraint solver. For parallel processing you can use a
    // /// different solver (see Extras/BulletMultiThreaded)
    // btSequentialImpulseConstraintSolver* sol = new btSequentialImpulseConstraintSolver;
    // m_solver = sol;

    // m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase,
    //                                               m_solver,m_collisionConfiguration);
    // m_dynamicsWorld->setDebugDrawer(&sDebugDrawer);
    // m_dynamicsWorld->getSolverInfo().m_splitImpulse=true;
    // m_dynamicsWorld->getSolverInfo().m_numIterations = 20;
    // m_dynamicsWorld->getDispatchInfo().m_useContinuous = m_ccdMode == USE_CCD;
    // m_dynamicsWorld->setGravity(btVector3(0,-10,0));

    // Create the ground
    // We can also use DemoApplication::localCreateRigidBody, but for clarity
    // it is provided here:
    {
        /// Create the shape for the ground
        btBoxShape* box = new btBoxShape(btVector3(btScalar(110.),
                                                   btScalar(1.),
                                                   btScalar(110.)));
        btCollisionShape* groundShape = box;
        //m_collisionShapes.push_back(groundShape);
        btScalar mass(0.);
        btVector3 localInertia(0,0,0);
        btTransform groundTransform;
        groundTransform.setIdentity();
        
        // using motionstate is recommended, it provides interpolation
        // capabilities, and only synchronizes 'active' objects
        btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState,
                                                        groundShape,localInertia);
        btRigidBody* body = new btRigidBody(rbInfo);
        body->setRestitution(.8);

        // add the body to the dynamics world
        m_dynamicsWorld->addRigidBody(body);
    }

    btVector3 localInertia(0,0,0);
    btCollisionShape* boxShape = new btBoxShape(btVector3(1,1,1));
    //m_collisionShapes.push_back(boxShape);
    boxShape->calculateLocalInertia(1.0f, localInertia);

    // ///  Create Dynamic Objects
    // {
    //     btScalar mass{5.f};
    //     m_rocketMesh = new StlMesh("../models/object.stl");
        
    //     btVector3 localInertia(0,0,0);
    //     btGImpactMeshShape *rocketShape = new btGImpactMeshShape(m_rocketMesh);
    //     rocketShape->updateBound();
    //     rocketShape->calculateLocalInertia(mass, localInertia);
        
    //     btVector3 pos(0,10,-5);
    //     btQuaternion rot(0,0,0,1);
    //     btTransform trans;
    //     trans.setIdentity();
    //     trans.setOrigin(pos);
    //     //trans.setRotation(rot);
    //     btDefaultMotionState *myMotionState = new btDefaultMotionState(trans);
    //     btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState,
    //                                                    rocketShape, localInertia);
    //     btRigidBody *body = new btRigidBody(cInfo);
    //     body->setContactProcessingThreshold(m_defaultContactProcessingThreshold);
    //     m_dynamicsWorld->addRigidBody(body);
    //     body->setRestitution(0.1);
    //     m_rocket = body;
    // }
}

void CcdPhysicsDemo::clientResetScene() {
    exitPhysics();
    initPhysics();
}

void CcdPhysicsDemo::keyboardCallback(unsigned char key, int x, int y) {
    if (key=='p') {
        switch (m_ccdMode) {
        case USE_CCD: {
            m_ccdMode = USE_NO_CCD;
            break;
        }
        case USE_NO_CCD:
        default: {
            m_ccdMode = USE_CCD;
        }
        };
        clientResetScene();
    } else if (key == 'w') {
        m_rocket->setActivationState(ACTIVE_TAG);
        //btVector3 impulse = m_rocket->getWorldTransform().getOrigin();
        auto ori = m_rocket->getOrientation();
        
        btVector3 thrust(0,1,0);
        btVector3 impulse = thrust.rotate(ori.getAxis(), ori.getAngle());
        float impulseStrength = 40.f;
        impulse *= impulseStrength;
        btVector3 relPos(0,0,0);//m_rocket->getCenterOfMassPosition();
        //relPos[1] -= 10;
        m_rocket->applyImpulse(impulse,relPos);
    } else {
        DemoApplication::keyboardCallback(key,x,y);
    }
}


void CcdPhysicsDemo::shootBox(const btVector3& destination) {
    if (m_dynamicsWorld) {
        float mass = 0.4f;
        btVector3 camPos = getCameraPosition();

        btTransform startTransform;
        startTransform.setIdentity();
        startTransform.setOrigin(camPos);

        setShootBoxShape ();

        btRigidBody* body = this->localCreateRigidBody(mass, startTransform, m_shootBoxShape);
        body->setLinearFactor(btVector3(1,1,1));
        body->setRestitution(0.2);

        btVector3 linVel(destination[0]-camPos[0],
                         destination[1]-camPos[1],
                         destination[2]-camPos[2]);
        linVel.normalize();
        linVel *= m_ShootBoxInitialSpeed;

        body->getWorldTransform().setOrigin(camPos);
        body->getWorldTransform().setRotation(btQuaternion(0,0,0,1));
        body->setLinearVelocity(linVel);
        body->setAngularVelocity(btVector3(0,0,0));
        body->setContactProcessingThreshold(1e30);

        /// when using m_ccdMode, disable regular CCD
        if (m_ccdMode==USE_CCD) {
            body->setCcdMotionThreshold(CUBE_HALF_EXTENTS);
            body->setCcdSweptSphereRadius(0.4f);
        }
    }
}

void CcdPhysicsDemo::exitPhysics() {
    // cleanup in the reverse order of creation/initialization

    // remove the rigidbodies from the dynamics world and delete them
    for (int i = m_dynamicsWorld->getNumCollisionObjects()-1; i != 0 ; --i) {
        btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[i];
        btRigidBody* body = btRigidBody::upcast(obj);
        if (body && body->getMotionState()) {
            delete body->getMotionState();
        }
        m_dynamicsWorld->removeCollisionObject( obj );
        delete obj;
    }

    // delete collision shapes
    // for (int j=0;j<m_collisionShapes.size();j++) {
    //     btCollisionShape* shape = m_collisionShapes[j];
    //     delete shape;
    // }
    // m_collisionShapes.clear();

    // delete m_dynamicsWorld;
    // delete m_solver;
    // delete m_broadphase;
    // delete m_dispatcher;
    // delete m_collisionConfiguration;
    delete m_rocketMesh;
}

