#include <QtOpenGL>
#include <vector>

struct polygon {
    float x, y, z;
};

class OpenGLObject {
    private:
        std::vector<struct polygon> polygons;

    public:
        void draw(float x, float y, float z);
};
