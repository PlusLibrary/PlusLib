#pragma once

#include <GLFW/glfw3.h>
#include <pluslib/util/list.h>
#include "color.h"
#include <pluslib/util/pointDouble.h>

class Graphics2D {
    public:
        void setColor(int r, int g, int b);
        void setColor(Color* color);
        void drawLine(double x0, double y0, double x1, double y1);
        void fillRect(double x, double y, double width, double height);
        void fillCircle(double centerX, double centerY, double radius);
        void pushMatrix();
        void popMatrix();
        void translate(double x, double y);
    private:
        void loadColor();
        void processVertices(GLenum type, List<PointDouble>* vertices);
};