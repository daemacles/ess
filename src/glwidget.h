#include <QtOpenGL>
#include <QImage>
#include <QTimeLine>
#include <QSvgRenderer>

class GLWidget : public QGLWidget
{
    Q_OBJECT

    public:
        GLWidget(QWidget *parent);
        ~GLWidget();

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
