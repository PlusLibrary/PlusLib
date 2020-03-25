#include <stdio.h>
#include <stdlib.h>

#include <pluslib/opengl/window.h>
#include <pluslib/opengl/graphics2d.h>
#include "ball.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int frameCounter = 0;
Window w;
Graphics2D graphics;
List<Ball> balls;

void render() {
    graphics.setColor(255, 0, 0);
    if (frameCounter++ % 10 == 0 && balls.size() < 512) {
        balls.add(new Ball(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
        printf("%f / %d / %d\n", w.time(), frameCounter, balls.size());
    }
    balls.forEach([](Ball* b) {
        b->render(&graphics, WINDOW_WIDTH, WINDOW_HEIGHT);
    });
}

int main() {
    w.setRenderCallback(render);
    w.show();
    return 0;
}