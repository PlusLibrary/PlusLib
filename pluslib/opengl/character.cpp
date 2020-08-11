#include <pluslib/opengl/character.h>

Character::Character(char16_t charCode, GLuint texture, unsigned int width, unsigned int height, int offset, int size) {
    this->charCode = charCode;
    this->texture = texture;
    this->width = width;
    this->height = height;
    this->offset = offset;
    this->size = size;
}

char16_t Character::getCharCode() {
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

int Character::getSize() {
    return this->size;
}