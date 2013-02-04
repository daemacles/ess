#include "LinearMath/btVector3.h"

#include "stlmesh.h"

using namespace std;

class BinaryReader {
    private:
    char *buffer;
    unsigned int size;
    unsigned int pos;

    public:
    BinaryReader(): buffer(nullptr), size(0), pos(0) {}

    BinaryReader(istream &is): buffer(nullptr), size(0), pos(0) {
        is.seekg (0, ios::end);
        size = is.tellg();
        is.seekg (0, ios::beg);

        buffer = new char[size];
        is.read(buffer, size);
        is.seekg(0, ios::beg);
    }
    
    ~BinaryReader () {
        delete[] buffer;
    }

    void setPos(int p) { pos = p; }
    int getPos() { return pos; }

    template <typename T>
    T next (void) {
        if (pos + sizeof(T) > size) {
            throw 20;
        }
        T *ptr = (T*)(buffer+pos);
        pos += sizeof(T);
        return *ptr;
    }
};

StlMesh::StlMesh(const string &filename, bool removeDuplicateVertices):
    btTriangleMesh (),
    openglobj(nullptr)
{
    ifstream is;
    is.open(filename, ios::binary);

    std::vector<btVector3*> polygons;

    BinaryReader reader(is);
    reader.setPos(80);        // skip the header

    try {
        int numTriangles = reader.next<uint32_t>();
        cout << "Found " << numTriangles << " triangles" << endl;

        for (int i = 0; i != numTriangles; ++i) {
            btVector3 normal(reader.next<float>(),
                             reader.next<float>(),
                             reader.next<float>());
            float x,y,z;
            x = reader.next<float>();
            y = reader.next<float>();
            z = reader.next<float>();
            btVector3 v0(x,z,y);
            polygons.push_back(new btVector3(x,z,y));
            x = reader.next<float>();
            y = reader.next<float>();
            z = reader.next<float>();
            polygons.push_back(new btVector3(x,z,y));
            btVector3 v1(x,z,y);
            x = reader.next<float>();
            y = reader.next<float>();
            z = reader.next<float>();
            polygons.push_back(new btVector3(x,z,y));
            btVector3 v2(x,z,y);
            uint16_t attribute_bytes = reader.next<uint16_t>();
            reader.setPos(reader.getPos() + attribute_bytes);
            addTriangle(v0, v1, v2, removeDuplicateVertices);
        }
    } catch (int e) {
        if (e == 20) {
            cout << "Oops, end of file" << endl;
        } else {
            cout << "Unknown exception" << endl;
        }
    }

#ifndef PHYS_DEMO    
    this->openglobj = new OpenGLObject(polygons);
#endif
}

StlMesh::~StlMesh() {
}
