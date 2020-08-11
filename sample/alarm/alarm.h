#pragma once

#include "toggleButton.h"

class Alarm {
    public:
        static int HEIGHT;
        Alarm();
        ToggleButton* getButton();
    private:
        int hour;
        int minute;
        ToggleButton* button;
};