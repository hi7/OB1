#include "controls.h"

Button::Button(uint16_t posx, uint16_t posy, uint16_t minimal_width, const char* text) {
    x = posx;
    y = posy;
    min_width = minimal_width;
    label = text;
}

void Button::draw(Arduino_TFT *gfx) {
    const uint16_t BORDER = 5;
    const uint16_t label_width = 6*strlen(label)+BORDER*2;
    gfx->fillRect(x, y, std::max(label_width, min_width), 12, 0xDFFC);
    gfx->setCursor(x+BORDER, y+1);
    gfx->setTextColor(BLACK);
    gfx->println(label);
}