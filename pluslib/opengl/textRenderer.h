#pragma once

#include <ft2build.h>
#include <GLFW/glfw3.h>
#include <pluslib/opengl/character.h>
#include <pluslib/util/list.h>
#include FT_FREETYPE_H

class TextRenderer {
    public:
        static TextRenderer* getInstance();
        Character* render(char16_t character, int size);
    private:
        TextRenderer();
        static TextRenderer* instance;
        static FT_Library* library;
        static FT_Face* face;
        static List<Character>* characterList;
        static int init();
};