#ifndef CONTROLS_H
#define CONTROLS_H

#include <algorithm>
#include <Arduino_TFT.h>

const uint8_t BTN = 5;

class Action  {
    public:
        virtual void start(Arduino_TFT *gfx);
        virtual void loop(Arduino_TFT *gfx);
};

class Button {
    uint16_t x, y, min_width;
    const char* label;
    bool active;
    Action* _action;
    public:
        Button(uint16_t x, uint16_t y, uint16_t minimal_width, const char* label, Action *action);
        uint16_t width(uint16_t actual);
        Action* action();
        void activate();
        void deactivate();
        void draw(Arduino_TFT *gfx);
};

bool buttonDown();
bool buttonUp();

#endif // CONTROLS_H