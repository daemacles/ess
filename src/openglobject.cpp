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
    this->color[0] = 0.5;
    this->color[1] = 0.5;
    this->color[2] = 0.5;
    this->color[3] = 1;
    printf("OpenGLObject created with %d polygons\n", polygons.size());
    this->polygons = std::vector<btVector3*>(polygons.size());
    for(int i = 0; i < this->polygons.size(); i++) {
        this->polygons[i] = polygons[i];
    }
    this->sprite = nullptr;
}


void OpenGLObject::draw(Pose& pose) {
    int ii = 0;

    //for(int i = 0; i < sizee; i++) {
        //printf("%p\n", &this->polygons);
        //printf("%p\n", &this->polygons[0]);
        //glVertex3f(this->polygons[i].x(), this->polygons[i].y(), this->polygons[i].z());
    //}

    glPushMatrix();
    //pose.worldTransform.getOpenGLMatrix(mat);
    //glTranslatef(pose.worldTransform.getOrigin().x(), pose.worldTransform.getOrigin().y(), pose.worldTransform.getOrigin().z());
    //
    //

    glTranslatef(pose.worldTransform.getOrigin().x(), pose.worldTransform.getOrigin().y(), pose.worldTransform.getOrigin().z());
    //glTranslatef(0, -10, 0);
    /*
    */

    btQuaternion quat = pose.worldTransform.getRotation();
    btVector3 axis = quat.getAxis();

    // bug:
    //glRotatef(quat.getAngle()*57.0, axis.x(), axis.y(), axis.z());
    glRotatef(quat.getAngle()*57.0, axis.x(), axis.y(), 0.0f);

    //printf("%f,%f,%f,%f\n", quat.getAngle(), axis.x(), axis.y(), axis.z());

    glBegin(GL_TRIANGLES);

     
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, this->color);
    for(auto vec : this->polygons) {
        //glTexCoord2f(sin(vec->x()), sin(vec->y()));
        //glColor3f(this->color.x(), this->color.y(), this->color.z());
        glVertex3f(vec->x(), vec->y(), vec->z());
    }
    //printf("[%d,%d,%d]\n", vec->x(), vec->y(), vec->z());

    glEnd();

    glPopMatrix();
    return;
}
#endif
