#include "alarm.h"

int Alarm::HEIGHT = 128;

Alarm::Alarm() {
    this->button = new ToggleButton();
}

ToggleButton* Alarm::getButton() {
    return this->button;
}