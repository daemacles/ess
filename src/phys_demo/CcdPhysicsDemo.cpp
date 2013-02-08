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

CcdPhysicsDemo::CcdPhysicsDemo(EntityHandler *_entities): entities(_entities)
{
    setDebugMode(btIDebugDraw::DBG_DrawText + btIDebugDraw::DBG_NoHelpText);
    setCameraDistance(btScalar(20.));
}

void CcdPhysicsDemo::clientMoveAndDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
 
    /// step the simulation
    if (m_dynamicsWorld) {
        //m_dynamicsWorld->stepSimulation(1./60.);
        // optional but useful: debug drawing
        //m_dynamicsWorld->debugDrawWorld();
    }

    entities->lock();
    renderme();
    entities->unlock();
    
    glFlush();
    swapBuffers();
}

void CcdPhysicsDemo::displayText() {
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

    btVector3 localInertia(0,0,0);
    btCollisionShape* boxShape = new btBoxShape(btVector3(1,1,1));
    boxShape->calculateLocalInertia(1.0f, localInertia);
}

void CcdPhysicsDemo::clientResetScene() {
}

void CcdPhysicsDemo::keyboardCallback(unsigned char key, int x, int y) {
    DemoApplication::keyboardCallback(key,x,y);
}


void CcdPhysicsDemo::shootBox(const btVector3& destination) {
    if (m_dynamicsWorld) {
        float mass = 01.0f;
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

        body->setCcdMotionThreshold(CUBE_HALF_EXTENTS);
        body->setCcdSweptSphereRadius(0.4f);
    }
}

void CcdPhysicsDemo::exitPhysics() {
}

