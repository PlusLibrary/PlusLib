#pragma once

class Color {
    public:
        Color(double r, double g, double b);
        Color(int r, int g, int b);
        void setColor(int r, int g, int b);
        void setColor(double r, double g, double b);
        double getR();
        double getG();
        double getB();
        static Color* fromHSB(double hue, double saturation, double brightness);
    private:
        double r;
        double g;
        double b;
};