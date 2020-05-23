#include <pluslib/opengl/character.h>

Character::Character(unsigned char charCode, GLuint texture, unsigned int width, unsigned int height, int offset) {
    this->charCode = charCode;
    this->texture = texture;
    this->width = width;
    this->height = height;
    this->offset = offset;
}

unsigned char Character::getCharCode() {
    return this->charCode;
}

GLuint Character::getTexture() {
    return this->texture;
}

unsigned int Character::getWidth() {
    return this->width;
}

unsigned int Character::getHeight() {
    return this->height;
}

int Character::getOffset() {
    return this->offset;
}