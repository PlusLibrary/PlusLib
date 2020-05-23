#include <math.h>

#include "ball.h"
#include <pluslib/opengl/graphics2d.h>
#include <pluslib/opengl/color.h>
#include <pluslib/util/random.h>

#define RADIUS 32
#define SPEED 4

Ball::Ball(double x, double y) {
    this->x = x;
    this->y = y;
    double angle = Random::getDouble();
    this->dx = SPEED * cos(angle * M_PI * 2);
    this->dy = SPEED * sin(angle * M_PI * 2);
    this->color = Color::fromHSB(Random::getDouble(), 0.25, 0.9375);
}

Ball::~Ball() {
    delete(this->color);
}

void Ball::render(Graphics2D* g, int width, int height) {
    this->x += dx;
    this->y += dy;
    dx = (this->x <= RADIUS || this->x >= width - RADIUS) ? -dx : dx;
    dy = (this->y <= RADIUS || this->y >= height - RADIUS) ? -dy : dy;
    g->setColor(this->color);
    g->fillCircle(x, y, RADIUS);
}