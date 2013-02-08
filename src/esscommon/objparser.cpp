#include "objparser.h"

#include <iostream>
#include <fstream>

#include "openglobject.h"

using namespace std;


OpenGLObject* OBJParser::parse(std::string filename) {
    std::string line;
    ifstream file;
    file.open("rocket01.obj");


    if(file.is_open()) {
        std::vector<btVector3*> polygons;

        while(file.good()) {
            getline(file, line);

            if(line[0] == 'v') {
                string str = line;


                int i;
                for(i = 0; str[i] != ' '; i++) {
                }
                int a = i + 1;
                for(i = a; str[i] != ' '; i++) {
                }
                int b = i + 1;
                for(i = b; str[i] != ' '; i++) {
                }
                int c = i + 1;

                for(int j = 0; j < str.length(); j++) {
                    if(str[j] == '.') {
                        str[j] = ',';
                    }
                }

                btVector3* vec = new btVector3((float) atof(str.substr(a, b - 1).c_str()),
                        (float) atof(str.substr(b, c - b - 1).c_str()),
                        (float) atof(str.substr(c, str.length() - b - c).c_str()));

                polygons.push_back(vec);

            } else if(line[0] == 'f') {

                printf("AAAAAAAAAAA\n");
                OpenGLObject* globject = new OpenGLObject(polygons);
                return globject;

            }
        }
        file.close();
    }

    return NULL;
}
