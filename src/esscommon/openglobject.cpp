#include "openglobject.h"
#include <stdio.h>
#include <math.h>

#include    <stdio.h>                         // Header File For Standard Input/Output ( NEW )

#ifndef PHYS_DEMO
#include <QtOpenGL>

void OpenGLObject::setColor(float* color) {
    this->color[0] = color[0];
    this->color[1] = color[1];
    this->color[2] = color[2];
    this->color[3] = color[3];
}

void OpenGLObject::setSprite(Sprite* sprite) {
    this->sprite = sprite;
}

OpenGLObject::OpenGLObject(std::vector<btVector3*> polygons) {
    this->color[0] = 1.0f;
    this->color[1] = 1.0f;
    this->color[2] = 0.0f;
    printf("OpenGLObject created with %d polygons\n", polygons.size());
    this->polygons = std::vector<btVector3*>(polygons.size());
    for(int i = 0; i < this->polygons.size(); i++) {
        this->polygons[i] = polygons[i];
    }
    this->sprite = nullptr;
}


void OpenGLObject::draw(Pose& pose) {
    glPushMatrix();

    glTranslatef(pose.worldTransform.getOrigin().x(), pose.worldTransform.getOrigin().y(), pose.worldTransform.getOrigin().z());

    btQuaternion quat = pose.worldTransform.getRotation();
    btVector3 axis = quat.getAxis();

    // bug:
    //glRotatef(quat.getAngle()*57.0, axis.x(), axis.y(), axis.z());
    glRotatef(quat.getAngle()*57.0, axis.x(), axis.y(), 0.0f);

    glBegin(GL_TRIANGLES);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, this->color);
        for(auto vec : this->polygons) {
            glVertex3f(vec->x(), vec->y(), vec->z());
        }
    glEnd();



    glPopMatrix();
}
#endif
