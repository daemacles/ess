#include "openglobject.h"
#include <stdio.h>
#include <math.h>

#include    <stdio.h>                         // Header File For Standard Input/Output ( NEW )

#ifndef PHYS_DEMO
#include <QtOpenGL>

void OpenGLObject::setColor(btVector3 color) {
    this->color = color;
}

OpenGLObject::OpenGLObject(std::vector<btVector3*> polygons) {
    this->color = btVector3(1,0,1);
    printf("OpenGLObject created with %d polygons\n", polygons.size());
    this->polygons = std::vector<btVector3*>(polygons.size());
    for(int i = 0; i < this->polygons.size(); i++) {
        this->polygons[i] = polygons[i];
        //printf("%d, %p\n", &polygons[i]);
        //glVertex3f(this->polygons[i].x(), this->polygons[i].y(), this->polygons[i].z());
    }
    //this->textureData = rgb_tga("moon.tga", &this->texW, &this->texH);
    /*
    this->polygons.resize(3);

    struct polygon pol1;
    pol1.x = 1;
    pol1.y = 1;
    pol1.z = 0;

    struct polygon pol2;
    pol2.x = 1;
    pol2.y = -1;
    pol2.z = 0;

    struct polygon pol3;
    pol3.x = -1;
    pol3.y = -1;
    pol3.z = 0;

    this->polygons.push_back(pol1);
    this->polygons.push_back(pol2);
    this->polygons.push_back(pol3);

    //this->polygons.insert(0, pol1);

    //glVertex3f(1.0f, 1.0f, 0.0f);
    //glVertex3f(1, -1, 0.0f);
    //glVertex3f(-1.0f, -1, 0.0f);
    */
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
    glTranslatef(0, -8, 0);

    printf("%f,%f,%f\n", pose.worldTransform.getOrigin().x(), pose.worldTransform.getOrigin().y(), pose.worldTransform.getOrigin().z());
    
    btQuaternion quat = pose.worldTransform.getRotation();
    btVector3 axis = quat.getAxis();
    glRotatef(quat.getAngle()*57, axis.x(), axis.y(), axis.z());

    //printf("%f,%f,%f,%f\n", quat.getAngle(), axis.x(), axis.y(), axis.z());

    //printf("%f\n", pose.worldTransform.getRotation().angle(btQuaternion(btVector3(0,1,0),0))*57.0);

    glBegin(GL_TRIANGLES);

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
