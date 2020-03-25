#include "color.h"
#include <math.h>

#define MAX_VALUE 255.0

Color::Color(int r, int g, int b) {
    setColor(r, g, b);
}

Color::Color(double r, double g, double b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

void Color::setColor(int r, int g, int b) {
    this->r = r / MAX_VALUE;
    this->g = g / MAX_VALUE;
    this->b = b / MAX_VALUE;
}

void Color::setColor(double r, double g, double b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

double Color::getR() {
    return this->r;
}

double Color::getG() {
    return this->g;
}

double Color::getB() {
    return this->b;
}

Color* Color::fromHSB(double h, double s, double b) {
    if (s == 0) {
        return new Color(b, b, b);
    }
    h = fmod(h, 1) * 6.0;
    double f = h - floor(h);
    double p = b * (1 - s);
    double q = b * (1 - s * f);
    double t = b * (1 - s * (1 - f));
    double out[] = {b, t, p, b, t, p, b, p, q, b, p, q, b};
    int convert[] = {0, 2, 4, 5, 1, 3};
    int o = convert[(int) h];
    return new Color(out[o * 2], out[o * 2 + 1], out[o * 2 + 2]);
}