#include <pluslib/opengl/graphics2d.h>
#include <pluslib/util/pointInt.h>

class ToggleButton {
    public:
        static constexpr double SMOOTH_CONSTANT = 2.0 / 3.0;
        ToggleButton();
        void render(Graphics2D* g);
        PointInt* getLocation();
        void setLocation(PointInt* p);
        void setRadius(double radius);
        void setKnobRadius(double radius);
        void setCenterRight(double x);
        bool hover(int x, int y);
        void click(int x, int y);
    private:
        static const int CHANGE_FRAME = 24;
        double smooth(double x);
        bool state;
        PointInt* location;
        double radius;
        double diameter;
        double knobRadius;
        double centerRight;
        double rectWidth;
        bool hovered;
        bool animating;
        int knobFrame;
        int direction;
};