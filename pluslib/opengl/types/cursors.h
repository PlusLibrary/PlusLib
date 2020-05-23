#pragma once
#include <GLFW/glfw3.h>

enum Cursor {
    NORMAL = GLFW_ARROW_CURSOR,
    HAND = GLFW_HAND_CURSOR,
};

class Cursors {
    public:
        static void init();
        static GLFWcursor* getCursor(Cursor cursor);
        static GLFWcursor* cursors[2];
};