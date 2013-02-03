#include <string>
#include "LinearMath/btVector3.h"

#include "openglobject.h"

class OBJParser {
    public:
        OpenGLObject* parse(std::string filename);
};
