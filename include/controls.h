#ifndef CONTROLS_H
#define CONTROLS_H

#include <algorithm>
#include <Arduino_TFT.h>

const uint8_t BTN = 5;

class Action  {
    public:
        void header(const char* name, Arduino_TFT *gfx);
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
bool isPressed();
unsigned long getStartTime();
void setStartTime(unsigned long time);
unsigned long buttonReleased();
void logAt(uint32_t i, uint16_t x, uint16_t y, Arduino_TFT *gfx, bool clear);
void logAt(size_t i, uint16_t x, uint16_t y, Arduino_TFT *gfx, bool clear);
void logAt(const char c, uint16_t x, uint16_t y, Arduino_TFT *gfx, bool clear);
void logAt(const char s[], uint16_t x, uint16_t y, Arduino_TFT *gfx, bool clear);
void logAt(char s[], uint16_t x, uint16_t y, Arduino_TFT *gfx, bool clear);
void log(const char s[], Arduino_TFT *gfx);
void log(char s[], Arduino_TFT *gfx);
void log(size_t n, Arduino_TFT *gfx);
void log(int8_t n, Arduino_TFT *gfx);

#endif // CONTROLS_H