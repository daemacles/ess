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
#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>
#include <btBulletDynamicsCommon.h>
#include "CcdPhysicsDemo.h"
#include "GlutStuff.h"
#include "GLDebugDrawer.h"
//#include <QtOpenGL>

#include "entityhandler.h"
#include "zmqhandler.h"
#include "simulator.h"
#include "rocket.h"
#include "pose.h"
#include "sensor.h"
#include "gyrosensor.h"

GLDebugDrawer gDebugDrawer;

void printPose(Pose &pose) {
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

int main(int argc, char **argv)
{
    EntityHandler entities;
    ZMQHandler networkHandler(1200);
    Simulator sim(&entities, &networkHandler);
    sim.start();
    
    if (argc == 2 && argv[1][0] == 'v') {
        Rocket *rocket = static_cast<Rocket*>(entities.dynamicEnts.at("rocket"));
        // GyroSensor *gyro = static_cast<GyroSensor*>(entities.sensors["gyro"]);
        for (int i = 0; i != 80; ++i) {
            //sim.stepSimulation(1./60.);
            std::chrono::milliseconds dura(100);
            std::this_thread::sleep_for(dura);
            
            auto pose = rocket->getPose();
            printPose(pose);
            // auto &angvel = gyro->getValue();
            // printf ("%9.4f %8.3f %8.3f %8.3f\n", gyro->getTimestamp(),
            //         angvel.x(), angvel.y(), angvel.z());
        }
    } else {
    
        CcdPhysicsDemo* ccdDemo = new CcdPhysicsDemo(&entities);
        ccdDemo->setDynamicsWorld(sim.getDynamicsWorld());
        ccdDemo->initPhysics();
        sim.getDynamicsWorld()->setDebugDrawer(&gDebugDrawer);
        printf ("##,##\n");
        printf ("timestamp,x,y,z\n");
        glutmain(argc, argv, 640, 480,
                 "Bullet Physics Demo. http://bulletphysics.com", ccdDemo);
        delete ccdDemo;
    }

    sim.stop();
    printf("Program finished, bye!\n");
    return 0;
}
