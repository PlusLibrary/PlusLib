#include "main.h"
#include <stdio.h>
#include <time.h>
#include <pluslib/opengl/window.h>
#include <pluslib/opengl/graphics2d.h>
#include <pluslib/opengl/color.h>
#include <pluslib/opengl/types/cursors.h>
#include <pluslib/opengl/textRenderer.h>
#include <pluslib/util/list.h>
#include "toggleButton.h"
#include "alarm.h"

#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 720

char16_t WEEKDAY[7][10] = {u"Sun", u"Mon", u"Tue", u"Wed", u"Thu", u"Fri", u"Sat"};
Window* window;
Graphics2D* graphics;
TextRenderer* textRenderer;
ToggleButton* tempButton = new ToggleButton(354, 96);
List<Alarm>* alarms = new List<Alarm>();
bool hovered = false;

int main() {
    init();
    textRenderer = TextRenderer::getInstance();
    window->show();
    return 0;
}

void render() { 
    tempButton->render(graphics);
    graphics->setColor(255, 255, 255);
    renderNowTime();
    renderAlarm();
}

void renderAlarm() {
    for (int i = 0; i < alarms->size(); i++) {
        
    }
}

void renderNowTime() {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    char16_t* nowString = (char16_t*) malloc(sizeof(char16_t) * 10);
    int weekday = t->tm_wday;
    nowString[0] = t->tm_hour / 10 + 48;
    nowString[1] = t->tm_hour % 10 + 48;
    nowString[2] = 58;
    nowString[3] = t->tm_min / 10 + 48;
    nowString[4] = t->tm_min % 10 + 48;
    nowString[5] = 58;
    nowString[6] = t->tm_sec / 10 + 48;
    nowString[7] = t->tm_sec % 10 + 48;
    nowString[8] = 0;
    graphics->setFontSize(24);
    graphics->drawText(nowString, -8, WINDOW_WIDTH);
    graphics->drawText(WEEKDAY[weekday], WINDOW_WIDTH - graphics->textWidth(WEEKDAY[weekday]) - 16, -8.0);
    delete(nowString);
}

void cursorMoved(int x, int y) {
    if (tempButton->hover(x, y)) {
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
    tempButton->click(x, y);
}

void init() {
    window = new Window();
    window->setRenderCallback(render);
    window->setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    window->setBackgroundColor(new Color(0, 0, 0));
    window->setTitle("Alarm");
    window->setCursorMovedCallback(cursorMoved);
    window->setCursorClickedCallback(cursorClicked);
    graphics = Graphics2D::getInstance();
}
