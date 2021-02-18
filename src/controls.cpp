#include "controls.h"

Button::Button(uint16_t posx, uint16_t posy, uint16_t minimal_width, const char* text, Action *anAction) {
    x = posx;
    y = posy;
    min_width = minimal_width;
    label = text;
    action = anAction;
    active = false;
}

uint16_t Button::width(uint16_t actual) {
    return std::max(actual, min_width);
}

void Button::start(Arduino_TFT *gfx) {
    action->start(gfx);
}

void Button::loop(Arduino_TFT *gfx) {
    action->loop(gfx);
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
    if(active) {
        gfx->fillRoundRect(x-3, y-3, width(label_width)+3, 16, 8, 0x07E0);
    } else {
        gfx->fillRoundRect(x-2, y, width(label_width), 12, 6, 0xDFFC);
    }
    gfx->setCursor(x+BORDER, y+1);
    gfx->setTextColor(BLACK);
    gfx->println(label);
}