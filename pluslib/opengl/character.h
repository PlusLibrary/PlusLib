#pragma once
#include <GLFW/glfw3.h>

class Character {
    public:
        Character(unsigned char charCode, GLuint texture, unsigned int width, unsigned int height, int offset);
        unsigned char getCharCode();
        unsigned int getWidth();
        unsigned int getHeight();
        GLuint getTexture();
        int getOffset();
    private:
        unsigned char charCode;
        unsigned int width;
        unsigned int height;
        GLuint texture;
        int offset;
};