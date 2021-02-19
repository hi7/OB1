#include "controls.h"

Button::Button(uint16_t posx, uint16_t posy, uint16_t minimal_width, const char* text, Action *action) {
    x = posx;
    y = posy;
    min_width = minimal_width;
    label = text;
    _action = action;
    active = false;
}

uint16_t Button::width(uint16_t actual) {
    return std::max(actual, min_width);
}

Action* Button::action() {
    return _action;
}

void Button::activate() {
    active = true;
}
void Button::deactivate() {
    active = false;
}

void Button::draw(Arduino_TFT *gfx) {
    const uint16_t BORDER = 5;
    const uint16_t label_width = 6*strlen(label)+BORDER*2;
    gfx->fillRect(x-3, y-3, width(label_width)+3, 16, WHITE);
    if(active) {
        gfx->fillRoundRect(x-3, y-3, width(label_width)+3, 16, 8, 0x07E0);
    } else {
        gfx->fillRoundRect(x-2, y, width(label_width), 12, 6, 0xDFFC);
    }
    gfx->setCursor(x+BORDER, y+1);
    gfx->setTextColor(BLACK);
    gfx->println(label);
}

bool buttonDown() {
    return digitalRead(BTN) == HIGH;
}

bool buttonUp() {
    return digitalRead(BTN) == LOW;
}

void logAt(const char s[], uint16_t x, uint16_t y, Arduino_TFT *gfx) {
    gfx->setCursor(x, y);
    gfx->setTextColor(BLUE);
    gfx->println(s);
}
void log(const char s[], Arduino_TFT *gfx) {
    logAt(s, 10, 10, gfx);
}

void log(size_t i, Arduino_TFT *gfx) {
    gfx->fillRect(90, 10, 40, 10, WHITE);
    gfx->setCursor(90, 10);
    gfx->setTextColor(BLACK);
    gfx->println(i);
}
