#include <pluslib/opengl/graphics2d.h>
#include <pluslib/opengl/color.h>

class Ball {
    public:
        Ball(double x, double y);
        ~Ball();
        void render(Graphics2D* g, int width, int height);
    private:
        double x;
        double y;
        double dx;
        double dy;
        Color* color;
};