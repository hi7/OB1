#ifndef CONTROLS_H
#define CONTROLS_H

#include <algorithm>
#include <Arduino_TFT.h>


class Action  {
    public:
        virtual void start(Arduino_TFT *gfx);
};

class Button {
    uint16_t x, y, min_width;
    const char* label;
    bool active;
    Action* action;
    public:
        Button(uint16_t x, uint16_t y, uint16_t minimal_width, const char* label, Action *anAction);
        uint16_t width(uint16_t actual);
        void activate();
        void deactivate();
        void start(Arduino_TFT *gfx);
        void draw(Arduino_TFT *gfx);
};

#endif // CONTROLS_H