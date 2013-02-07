#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <stdint.h>
#include <string>

class Sprite {
    private:
    Sprite (char* data, int width, int height);

    public:
    char *data;
    int width;
    int height;
    static Sprite* loadFromFile (std::string bmpFile);
    virtual ~Sprite ();
};

#endif
