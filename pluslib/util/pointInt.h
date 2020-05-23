#pragma once
#include <math.h>

class PointInt {
    public:
        int x;
        int y;
        PointInt(int x, int y);
        static double distance(PointInt* p0, PointInt* p1);
        static double distance(int x0, int y0, int x1, int y1);
};