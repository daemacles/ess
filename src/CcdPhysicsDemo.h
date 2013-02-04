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

#ifndef BT_CCD_PHYSICS_DEMO_H
#define BT_CCD_PHYSICS_DEMO_H

#include "GlutDemoApplication.h"
#define PlatformDemoApplication GlutDemoApplication

#include "LinearMath/btAlignedObjectArray.h"
#include "stlmesh.h"

class btBroadphaseInterface;
class btCollisionShape;
class btOverlappingPairCache;
class btCollisionDispatcher;
class btConstraintSolver;
struct btCollisionAlgorithmCreateFunc;
class btDefaultCollisionConfiguration;

/// CcdPhysicsDemo is good starting point for learning the code base and porting.

class CcdPhysicsDemo : public PlatformDemoApplication
{
    private:
    int m_ccdMode;

    public:

    CcdPhysicsDemo();
    virtual ~CcdPhysicsDemo() { exitPhysics(); }

    void         initPhysics();
    void         setDynamicsWorld (btDynamicsWorld *world);
    void	 exitPhysics();
    virtual void clientMoveAndDisplay();
            void displayText();
    virtual void keyboardCallback(unsigned char key, int x, int y);
    virtual void displayCallback();
    virtual void shootBox(const btVector3& destination);
    virtual void clientResetScene();

    void callback (btScalar timeStep);
    
    static DemoApplication* Create()
    {
        CcdPhysicsDemo* demo = new CcdPhysicsDemo;
        demo->myinit();
        demo->initPhysics();
        return demo;
    }
};

#endif //BT_CCD_PHYSICS_DEMO_H

