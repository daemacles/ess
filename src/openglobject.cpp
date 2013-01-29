#include "openglobject.h"

OpenGLObject::OpenGLObject(std::vector<polygon> polygons) {

    this->polygons = polygons;
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

void OpenGLObject::draw(float x, float y, float z) {

    glBegin(GL_TRIANGLES);

    printf("%d\n", this->polygons.size());

    printf("DARRRRRRRRw\n");
    for(int i = 0; i != this->polygons.size(); i++) {
        glVertex3f(this->polygons[i].x, this->polygons[i].y, this->polygons[i].z);
    }
    printf("DONE\n");

    glEnd();

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
