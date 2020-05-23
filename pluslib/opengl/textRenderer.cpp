#include <pluslib/opengl/textRenderer.h>

#define SIZE 48

TextRenderer* TextRenderer::instance;
FT_Library* TextRenderer::library;
FT_Face* TextRenderer::face;
List<Character>* TextRenderer::characterList;

TextRenderer::TextRenderer() {
    
}

Character* TextRenderer::render(unsigned char character) {
    for (int i = 0; i < characterList->size(); i++) {
        Character* c = characterList->get(i);
        if (character == c->getCharCode()) {
            return c;
        }
    }
    FT_Load_Glyph(*TextRenderer::face, FT_Get_Char_Index(*TextRenderer::face, character), FT_LOAD_RENDER);
    FT_Bitmap* bitmap = new FT_Bitmap();
    bitmap = &((*TextRenderer::face)->glyph->bitmap);
    GLuint texture;
    glGenTextures (1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, bitmap->width, bitmap->rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE, bitmap->buffer);
    Character* c = new Character(character, texture, bitmap->width, bitmap->rows, SIZE - (*TextRenderer::face)->glyph->bitmap_top);
    characterList->add(c);
    return c;
}

int TextRenderer::init() {
    characterList = new List<Character>();
    int error = FT_Init_FreeType(TextRenderer::library = new FT_Library());
    if (error) {
        printf("freeType init error\n");
        return -1;
    }
    error = FT_New_Face(*TextRenderer::library, "/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf", 0, TextRenderer::face = new FT_Face());
    if (error == FT_Err_Unknown_File_Format) {
        printf("freeType: unknown file format\n");
        return -1;
    } else if (error) {
        printf("freeType: unknown error.\n");
        return -1;
    }
    FT_Set_Pixel_Sizes(*face, 0, SIZE);
    return 0;
}

TextRenderer* TextRenderer::getInstance() {
    if (TextRenderer::instance == nullptr && !init()) {
        TextRenderer::instance = new TextRenderer();
    }
    return TextRenderer::instance;
}