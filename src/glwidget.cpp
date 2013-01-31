#include <QtGui/QImage>
#include <math.h>

#include "glwidget.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

    GLWidget::GLWidget(QWidget *parent)
: QGLWidget(QGLFormat(QGL::SampleBuffers|QGL::AlphaChannel), parent)
{
    makeCurrent();
    glViewport(0,0,768,480);
    QPainter p(this);
    return;
}

GLWidget::~GLWidget()
{
    delete[] wave;
    glDeleteLists(tile_list, 1);
    delete texture_fbo;
    if (render_fbo != texture_fbo)
        delete render_fbo;
}

void GLWidget::beginDraw() {
#define ZOOM_1 10.0
    glMatrixMode(GL_PROJECTION);
    glOrtho(-ZOOM_1, ZOOM_1, -ZOOM_1, ZOOM_1, 0.0, 10);

    glMatrixMode(GL_MODELVIEW);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void GLWidget::endDraw() {
    glFlush();
}

void GLWidget::draw()
{
    glBegin(GL_TRIANGLES);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1, -1, 0.0f);
    glVertex3f(-1.0f, -1, 0.0f);
    glEnd();


    return;
}
