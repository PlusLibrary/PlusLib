#include <pluslib/opengl/graphics2d.h>
#include <pluslib/util/pointInt.h>

class ToggleButton {
    public:
        ToggleButton();
        void render(Graphics2D g);
        PointInt* getLocation();
        void setLocation(PointInt* p);
        void setRadius(double radius);
        void setKnobRadius(double radius);
        void setCenterRight(double x);
    private:
        PointInt* location;
        double radius;
        double diameter;
        double knobRadius;
        double centerRight;
        double rectWidth;
};