#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "openglobject.h"

#include "pose.h"

class Entity {
    private:
        Pose* pose;
        OpenGLObject* openglobj;
    public:
        Entity(OpenGLObject* openglobj, Pose* pose);
        OpenGLObject* getOpenGLObject();
};

#endif
