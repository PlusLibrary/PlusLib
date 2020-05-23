#include <pluslib/opengl/types/cursors.h>
#define cursor(v) glfwCreateStandardCursor(v)
#define COUNT 2

GLFWcursor* Cursors::cursors[COUNT];

void Cursors::init() {
    cursors[0] = cursor(GLFW_ARROW_CURSOR);
    cursors[1] = cursor(GLFW_HAND_CURSOR);
}

GLFWcursor* Cursors::getCursor(Cursor cursor) {
    switch (cursor) {
        case Cursor::NORMAL:
            return cursors[0];
        case Cursor::HAND:
            return cursors[1];
    }
}