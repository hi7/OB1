#include "bounce.h"

Bounce::Bounce(uint8_t buttonPin)
    : Action() {
        button = buttonPin;
}

void Bounce::start(Arduino_TFT *gfx) {
    gfx->fillScreen(WHITE);
}

void Bounce::loop(Arduino_TFT *gfx) {
    //gfx->fillScreen(WHITE);
}