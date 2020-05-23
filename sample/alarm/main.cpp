#include "main.h"
#include <stdio.h>
#include <pluslib/opengl/window.h>
#include <pluslib/opengl/graphics2d.h>
#include <pluslib/opengl/color.h>
#include <pluslib/opengl/types/cursors.h>
#include "toggleButton.h"
#include <pluslib/opengl/textRenderer.h>

#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 720

#define PADDING 16

Window* window;
Graphics2D* graphics;
TextRenderer* textRenderer;
ToggleButton button;
bool hovered = false;

int main() {
    init();
    textRenderer = TextRenderer::getInstance();
    window->show();
    return 0;
}

void render() { 
    button.render(graphics);
    graphics->setColor(255, 0, 0);
    graphics->fillRect(0, 100, 200, 48);
    graphics->setColor(255, 255, 255);
    graphics->drawText("Hello World-_0123456789あ", 0, 100);
    
}

void cursorMoved(int x, int y) {
    if (button.hover(x, y)) {
        if (!hovered) {
            window->setCursor(Cursor::HAND);
            hovered = true;
        }
    } else if (hovered) {
        window->setCursor(Cursor::NORMAL);
        hovered = false;
    }
}

void cursorClicked(int x, int y) {
    button.click(x, y);
}

void init() {
    window = new Window();
    window->setRenderCallback(render);
    window->setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    window->setBackgroundColor(new Color(0, 0, 0));
    window->setTitle("Alarm");
    window->setCursorMovedCallback(cursorMoved);
    window->setCursorClickedCallback(cursorClicked);
    button.setLocation(new PointInt(256, 50));
    graphics = Graphics2D::getInstance();
}
