#pragma once

#include <GLFW/glfw3.h>
#include <pluslib/util/list.h>
#include <pluslib/util/pointInt.h>
#include <pluslib/opengl/color.h>
#include <pluslib/opengl/types/cursors.h>

class Window {
    public:
        Window();
        void show();
        void setSize(int width, int height);
        void setTitle(const char* title);
        void setBackgroundColor(Color* color);
        void setRenderCallback(void (*callback) (void));
        void setKeyCallback(void (*callback) (int, int));
        void setCursorMovedCallback(void (*callback) (int, int));
        void setCursorClickedCallback(void (*callback) (int, int));
        void setCursor(Cursor cursor);
        double time();
    private:
        GLFWwindow* window;
        static void (*cursorMovedCallback) (int, int);
        static void (*cursorClickedCallback) (int, int);
        static void (*keyCallback) (int, int);
        static void (*renderCallback) (void);
};