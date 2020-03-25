#include "toggleButton.h"
#include <pluslib/opengl/graphics2d.h>
#include <pluslib/util/pointInt.h>

#define COLOR_ON_R 48
#define COLOR_ON_G 209
#define COLOR_ON_B 88

#define COLOR_KNOB_R 255
#define COLOR_KNOB_G 255
#define COLOR_KNOB_B 255

#define DEFAULT_RADIUS 24
#define DEFAULT_KNOB_RATIO 0.85
#define DEFAULT_INTERVAL_RATIO 2.5

ToggleButton::ToggleButton() {
    this->location = new PointInt(0, 0);
    setRadius(DEFAULT_RADIUS);
    setKnobRadius(DEFAULT_RADIUS * DEFAULT_KNOB_RATIO);
    setCenterRight(this->radius * DEFAULT_INTERVAL_RATIO);
}

void ToggleButton::render(Graphics2D g) {
    g.pushMatrix();
    g.translate(this->location->x, this->location->y);
    g.setColor(COLOR_ON_R, COLOR_ON_G, COLOR_ON_B);
    g.fillCircle(this->radius, this->radius, this->radius);
    g.fillCircle(this->centerRight, this->radius, this->radius);
    g.fillRect(this->radius, 0, this->rectWidth, this->diameter);
    g.setColor(COLOR_KNOB_R, COLOR_KNOB_G, COLOR_KNOB_B);
    g.fillCircle(this->radius, this->radius, this->knobRadius);
    g.popMatrix();
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