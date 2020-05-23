#include "toggleButton.h"

#define COLOR_ON_R 48
#define COLOR_ON_G 209
#define COLOR_ON_B 88
#define COLOR_OFF_R 38
#define COLOR_OFF_G 38
#define COLOR_OFF_B 41
#define COLOR_DIFF_R (COLOR_ON_R - COLOR_OFF_R)
#define COLOR_DIFF_G (COLOR_ON_G - COLOR_OFF_G)
#define COLOR_DIFF_B (COLOR_ON_B - COLOR_OFF_B)
#define COLOR_KNOB_R 255
#define COLOR_KNOB_G 255
#define COLOR_KNOB_B 255

#define DEFAULT_RADIUS 24
#define DEFAULT_KNOB_RATIO 0.85
#define DEFAULT_INTERVAL_RATIO 2.5

ToggleButton::ToggleButton() {
    this->location = new PointInt(0, 0);
    this->hovered = 0;
    this->knobFrame = 0;
    this->direction = 0;
    setRadius(DEFAULT_RADIUS);
    setKnobRadius(DEFAULT_RADIUS * DEFAULT_KNOB_RATIO);
    setCenterRight(this->radius * DEFAULT_INTERVAL_RATIO);
}

void ToggleButton::render(Graphics2D* g) {
    g->pushMatrix();
    g->translate(this->location->x, this->location->y);
    if (this->animating) {
        knobFrame += this->state ? 1 : -1;
        if (this->knobFrame >= ToggleButton::CHANGE_FRAME || this->knobFrame <= 0) {
            this->animating = false;
        }
    }
    double change = smooth((double) this->knobFrame / ToggleButton::CHANGE_FRAME);
    g->setColor(COLOR_OFF_R + (int) (COLOR_DIFF_R * change), COLOR_OFF_G + (int) (COLOR_DIFF_G * change), COLOR_OFF_B + (int) (COLOR_DIFF_B * change));
    g->fillCircle(this->radius, this->radius, this->radius);
    g->fillCircle(this->centerRight, this->radius, this->radius);
    g->fillRect(this->radius, 0, this->rectWidth, this->diameter);
    g->setColor(COLOR_KNOB_R, COLOR_KNOB_G, COLOR_KNOB_B);
    g->pushMatrix();
    g->translate((this->centerRight - this->radius) * change, 0);
    g->fillCircle(this->radius, this->radius, this->knobRadius);
    g->popMatrix();
    g->popMatrix();
}

double ToggleButton::smooth(double x) {
    return (-4.0 / 3.0 * (x * x * x) + 2 * (x * x)) / ToggleButton::SMOOTH_CONSTANT;
}

bool ToggleButton::hover(int x, int y) {
    x -= this->location->x;
    y -= this->location->y;
    return (x >= this->radius && x <= this->radius + this->rectWidth && y >= 0 && y <= this->diameter) || PointInt::distance(x, y, this->radius, this->radius) < this->radius || PointInt::distance(x, y, this->centerRight, this->radius) < this->radius;
}

void ToggleButton::click(int x, int y) {
    if (!this->animating && hover(x, y)) {
        this->animating = true;
        this->state = !this->state;
        this->direction = this->state ? 1 : -1;
    }
}

void ToggleButton::setLocation(PointInt* p) {
    delete(this->location);
    this->location = new PointInt(p->x, p->y);
}

void ToggleButton::setRadius(double radius) {
    this->radius = radius;
    this->diameter = radius * 2;
}

void ToggleButton::setKnobRadius(double radius) {
    this->knobRadius = radius;
}

void ToggleButton::setCenterRight(double x) {
    this->centerRight = x;
    this->rectWidth = x - this->radius;
}

PointInt* ToggleButton::getLocation() {
    return this->location;
}