#include "window.h"

#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720

int windowWidth = DEFAULT_WINDOW_WIDTH;
int windowHeight = DEFAULT_WINDOW_HEIGHT;
void (*Window::renderCallback) (void);
void (*Window::keyCallback) (int, int);
void (*Window::cursorMovedCallback) (int, int);
void (*Window::cursorClickedCallback) (int, int);


Window::Window() {
    glfwInit();
    Cursors::init();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 16);
    this->window = glfwCreateWindow(windowWidth, windowHeight, "Window", NULL, NULL);
    glfwMakeContextCurrent(window);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glfwSwapInterval(1);
    glViewport(0, 0, windowWidth, windowHeight);
    glOrtho(0, windowWidth, windowHeight, 0, -1.0, 1.0);
}

void Window::setSize(int width, int height) {
    glfwSetWindowSize(this->window, width, height);
}

void Window::setTitle(const char* title) {
    glfwSetWindowTitle(this->window, title);
}

void Window::setBackgroundColor(Color* color) {
    glClearColor(color->getR(), color->getG(), color->getB(), 1.0f);
}

void Window::setRenderCallback(void (*callback) (void)) {
    Window::renderCallback = callback;
}

void Window::setKeyCallback(void (*callback) (int, int)) {
    Window::keyCallback = callback;
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scanCode, int action, int mods) {
        Window::keyCallback(key, action);
    });
}

void Window::setCursorMovedCallback(void (*callback) (int, int)) {
    Window::cursorMovedCallback = callback;
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
        Window::cursorMovedCallback((int) x, (int) y);
    });
}

void Window::setCursorClickedCallback(void (*callback) (int, int)) {
    Window::cursorClickedCallback = callback;
    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
        double doubleX, doubleY;
        glfwGetCursorPos(window, &doubleX, &doubleY);
        Window::cursorClickedCallback((int) doubleX, (int) doubleY);
    });
}

void Window::setCursor(Cursor cursor) {
    glfwSetCursor(this->window, Cursors::getCursor(cursor));
}

double Window::time() {
    return glfwGetTime();
}

void Window::show() {
    glfwShowWindow(window);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        renderCallback();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}