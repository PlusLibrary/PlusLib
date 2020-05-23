#include "pointInt.h"

PointInt::PointInt(int x, int y) {
    this->x = x;
    this->y = y;
}

double PointInt::distance(PointInt* p0, PointInt* p1) {
    return sqrt((p0->x - p1->x) * (p0->x - p1->x)) + ((p0->y - p1->y) * (p0->y - p1->y));
}

double PointInt::distance(int x0, int y0, int x1, int y1) {
    return sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
}