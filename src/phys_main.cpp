/*
  Bullet Continuous Collision Detection and Physics Library Copyright (c)
  2003-2006 Erwin Coumans http://continuousphysics.com/Bullet/

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

#include <cstdio>
#include <cmath>
#include <btBulletDynamicsCommon.h>
#include "CcdPhysicsDemo.h"
#include "GlutStuff.h"
#include "GLDebugDrawer.h"
//#include <QtOpenGL>

#include "simulator.h"
#include "rocket.h"

GLDebugDrawer gDebugDrawer;

#ifndef PHYS_DEMO
int phys_main(int argc, char **argv)
#else
int main(int argc, char **argv)
#endif
{
    EntityHandler entities;
    Simulator sim(&entities);
    
    btDynamicsWorld *world = sim.getDynamicsWorld();
    
    CcdPhysicsDemo* ccdDemo = new CcdPhysicsDemo();
    ccdDemo->setDynamicsWorld(world);
    ccdDemo->initPhysics();
    world->setDebugDrawer(&gDebugDrawer);
    world->setInternalTickCallback(simCallback, static_cast<void*>(&sim));
    
    glutmain(argc, argv, 640, 480,
             "Bullet Physics Demo. http://bulletphysics.com", ccdDemo);

    if (argc == 2) {
        printf ("timestamp x y z phi theta psi\n");
        Rocket *rocket = static_cast<Rocket*>(entities.dynamicEnts.at("rocket"));
        auto &poseHistory = rocket->getPoseHistory();
        for (auto &pose : poseHistory) {
            btVector3 position = pose.worldTransform.getOrigin();
            btQuaternion q = pose.worldTransform.getRotation();
            double q0 = q.x();
            double q1 = q.y();
            double q2 = q.z();
            double q3 = q.w();
            double phi = atan2(2*(q0*q1 + q2*q3), 1 - 2*(q1*q1 + q2*q2));
            double theta = asin(2*(q0*q2 - q3*q1));
            double psi = atan2(2*(q0*q3 + q1*q2), 1 - 2*(q2*q2 + q3*q3));
            printf("%9.4f %8.3f %8.3f %8.3f %8.3f %8.3f %8.3f\n",
                   pose.timestamp,
                   position.getX(), position.getY(), position.getZ(),
                   phi, theta, psi);
        }
    }
    printf("Program finished, bye!\n");
    delete ccdDemo;
    return 0;
}
