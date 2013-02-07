#include "sprite.h"

#include <QtOpenGL>
#include <stdio.h>
#include <malloc.h>

Sprite::Sprite(char* data, int width, int height) {
    this->data = data;
    this->width = width;
    this->height = height;
}

Sprite* Sprite::loadFromFile(char* bmpFile) {
    FILE* bmp = fopen(bmpFile, "r");

    fseek(bmp, 18, SEEK_SET);

    uint32_t width;
    uint32_t height;
    fread(&width, 1, 4, bmp);
    fread(&height, 1, 4, bmp);

    char* image = (char*) malloc(4 * width * width);

    fseek(bmp, 14 + 12 + 5, SEEK_SET);
    char buf[3];

    for(int i=0; i < height*width; i++) {
        fread(buf, 1, 3, bmp);
        image[4*i] = (GLubyte) buf[0];
        image[4*i + 1] = (GLubyte) buf[1];
        image[4*i + 2] = (GLubyte) buf[2];
        image[4*i + 3] = (GLubyte) 255;
    }

    fclose(bmp);
    
    return new Sprite(image, width, height);
}
