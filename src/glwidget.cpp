#include <QtGui/QImage>
#include "glwidget.h"

#include <math.h>

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

    GLWidget::GLWidget(QWidget *parent)
: QGLWidget(QGLFormat(QGL::SampleBuffers|QGL::AlphaChannel), parent)
{
    //makeCurrent();
    draw();
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

void GLWidget::draw()
{
    QPainter p(this); // used for text overlay

    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
    glBegin(GL_QUADS);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();

    glFlush();

    return;
}

void GLWidget::GLResize(int width, int height) {
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#else
    glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}
