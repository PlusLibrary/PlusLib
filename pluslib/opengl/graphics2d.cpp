#include <GLFW/glfw3.h>
#include <math.h>
#include <pluslib/util/list.h>
#include "graphics2d.h"
#include "color.h"
#include <pluslib/util/pointDouble.h>

#define COLOR_MAX 256.0
#define CIRCLE_DETAIL_RATIO 1

Color color(0, 0, 0);

void Graphics2D::setColor(int r, int g, int b) {
    color.setColor(r, g, b);
}

void Graphics2D::setColor(Color* c) {
    color.setColor(c->getR(), c->getG(), c->getB());
}

void Graphics2D::drawLine(double x0, double y0, double x1, double y1) {
    List<PointDouble>* points = new List<PointDouble>();
    glBegin(GL_LINES);
    points->add(new PointDouble(x0, y0));
    points->add(new PointDouble(x1, y1));
    processVertices(GL_LINES, points);
    delete(points);
}

void Graphics2D::fillRect(double x, double y, double width, double height) {
    List<PointDouble>* points = new List<PointDouble>();
    points->add(new PointDouble(x, y));
    points->add(new PointDouble(x, y + height));
    points->add(new PointDouble(x + width, y + height));
    points->add(new PointDouble(x + width, y));
    processVertices(GL_QUADS, points);
    delete(points);
}

void Graphics2D::fillCircle(double centerX, double centerY, double radius) {
    List<PointDouble>* points = new List<PointDouble>();
    int detail = radius * CIRCLE_DETAIL_RATIO;
    for (int i = 0; i < detail; i++) {
        double x = cos(M_PI * 2 * i / detail) * radius + centerX;
        double y = sin(M_PI * 2 * i / detail) * radius + centerY;
        points->add(new PointDouble(x, y));
    }
    processVertices(GL_POLYGON, points);
    delete(points);
}

void Graphics2D::loadColor() {
    glColor3d(color.getR(), color.getG(), color.getB());
}

void Graphics2D::processVertices(GLenum type, List<PointDouble>* vertices) {
    loadColor();
    glBegin(type);
    vertices->forEach([](PointDouble* p) { 
        glVertex2d(p->x, p->y);
    });
    glEnd();
}

void Graphics2D::pushMatrix() {
    glPushMatrix();
}

void Graphics2D::popMatrix() {
    glPopMatrix();
}

void Graphics2D::translate(double x, double y) {
    glTranslated(x, y, 0);
}