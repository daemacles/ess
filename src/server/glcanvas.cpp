#include <QtGui/QImage>
#include <math.h>

#include "glcanvas.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

GLCanvas::GLCanvas(QWidget *parent):
    QGLWidget(QGLFormat(QGL::SampleBuffers|QGL::AlphaChannel), parent)
{
    makeCurrent();
    glViewport(0, 0, GL_WIDTH, GL_HEIGHT);
    QPainter p(this);

    return;
}

GLCanvas::~GLCanvas()
{
    delete[] wave;
    glDeleteLists(tile_list, 1);
    delete texture_fbo;
    if (render_fbo != texture_fbo)
        delete render_fbo;
}

void GLCanvas::beginDraw() {
#define ZOOM_1 50.0
    glMatrixMode(GL_PROJECTION);
    glOrtho(-ZOOM_1, ZOOM_1, -ZOOM_1, ZOOM_1, -100.0, 1000);
    glTranslatef(0, -35, 0);
    glRotatef(15, 1, 0, 0);

    glMatrixMode(GL_MODELVIEW);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void GLCanvas::endDraw() {
    glFlush();
}
