#pragma once

#include <GLFW/glfw3.h>
#include <math.h>
#include <pluslib/opengl/color.h>
#include <pluslib/opengl/textRenderer.h>
#include <pluslib/opengl/character.h>
#include <pluslib/util/list.h>
#include <pluslib/util/pointDouble.h>

class Graphics2D {
    public:
        static Graphics2D* getInstance();
        void setColor(int r, int g, int b);
        void setColor(Color* color);
        void drawText(char* text, double x, double y);
        void drawLine(double x0, double y0, double x1, double y1);
        void fillRect(double x, double y, double width, double height);
        void fillCircle(double centerX, double centerY, double radius);
        void pushMatrix();
        void popMatrix();
        void translate(double x, double y);
    private:
        static Graphics2D* instance;
        Graphics2D();
        void loadColor();
        void processVertices(GLenum type, List<PointDouble>* vertices);
        Color* color;
        TextRenderer* textRenderer;
};