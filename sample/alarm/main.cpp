#include "main.h"
#include <stdio.h>
#include <pluslib/opengl/window.h>
#include <pluslib/opengl/graphics2d.h>
#include <pluslib/opengl/color.h>
#include "toggleButton.h"

#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 720

#define PADDING 16

struct Block;

Window* window;
Graphics2D graphics;
ToggleButton button;

int main() {
    init();
    window->show();
    return 0;
}

void render() { 
    button.render(graphics);
}

void cursorMoved(int x, int y) {
    printf("%d, %d\n", x, y);
}

void init() {
    window = new Window();
    window->setRenderCallback(render);
    window->setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    window->setBackgroundColor(new Color(0, 0, 0));
    window->setTitle("Alarm");
    window->setCursorMovedCallback(cursorMoved);
    button.setLocation(new PointInt(256, 0));
}