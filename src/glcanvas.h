#ifndef _GLCANVAS_H_
#define _GLCANVAS_H_

#include <QtOpenGL>
#include <QImage>
#include <QTimeLine>
#include <QSvgRenderer>

class GLCanvas : public QGLWidget
{
    Q_OBJECT

    public:
        GLCanvas(QWidget *parent);
        ~GLCanvas();

        void saveGLState();
        void restoreGLState();

        public slots:
            void beginDraw();
            void endDraw();
            void draw();

    private:
        QPoint anchor;
        float scale;
        float rot_x, rot_y, rot_z;
        GLuint tile_list;
        GLfloat *wave;

        QImage logo;
        QTimeLine *anim;
        QSvgRenderer *svg_renderer;
        QGLFramebufferObject *render_fbo;
        QGLFramebufferObject *texture_fbo;
};

#endif
