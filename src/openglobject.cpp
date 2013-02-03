#include "openglobject.h"
#include <stdio.h>

#ifndef PHYS_DEMO
#include <QtOpenGL>

OpenGLObject::OpenGLObject(std::vector<btVector3*> polygons) {
    printf("OpenGLObject created with %d polygons\n", polygons.size());
    this->polygons = std::vector<btVector3*>(polygons.size());
    for(int i = 0; i < this->polygons.size(); i++) {
        this->polygons[i] = polygons[i];
        //printf("%d, %p\n", &polygons[i]);
        //glVertex3f(this->polygons[i].x(), this->polygons[i].y(), this->polygons[i].z());
    }
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

void OpenGLObject::draw(Pose* pose) {
    int ii = 0;

    //for(int i = 0; i < sizee; i++) {
        //printf("%p\n", &this->polygons);
        //printf("%p\n", &this->polygons[0]);
        //glVertex3f(this->polygons[i].x(), this->polygons[i].y(), this->polygons[i].z());
    //}

    glPushMatrix();
    //glRotatef(pose->worldTransform.x(), pose->worldTransform.y(), pose->worldTransform.z(), 45);
    //pose->worldTransform.getOpenGLMatrix(mat);
    glTranslatef(pose->worldTransform.getOrigin().x(), pose->worldTransform.getOrigin().y(), pose->worldTransform.getOrigin().z());
    glRotatef(pose->worldTransform.getOrigin().x(), pose->worldTransform.getOrigin().y(), pose->worldTransform.getOrigin().z(), 90);
    glBegin(GL_TRIANGLES);

    for(auto vec : this->polygons) {
        glVertex3f(vec->x(), vec->y(), vec->z());
    }

    glEnd();

    glPopMatrix();
    return;

    /*
    glClearColor(1.0, 1.0, 0.0, 1.0);
    //glClear(GL_COLOR_BUFFER_BIT);
    //glLoadIdentity();
    //glTranslatef(0.0, 0.0, -5.0);
    glBegin(GL_QUADS);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 0.5f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();

    glFlush();
    */
}
#endif
