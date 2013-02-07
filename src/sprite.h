#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <stdint.h>

class Sprite {
    private:

        Sprite(char* data, int width, int height);
    public:
        char* data;
        int width;
        int height;
        static Sprite* loadFromFile(char* bmpFile);
};

#endif
