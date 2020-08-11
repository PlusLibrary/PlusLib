#pragma once
#include <GLFW/glfw3.h>

class Character {
    public:
        Character(char16_t charCode, GLuint texture, unsigned int width, unsigned int height, int offset, int size);
        char16_t getCharCode();
        unsigned int getWidth();
        unsigned int getHeight();
        GLuint getTexture();
        int getOffset();
        int getSize();
    private:
        char16_t charCode;
        unsigned int width;
        unsigned int height;
        GLuint texture;
        int offset;
        int size;
};