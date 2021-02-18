#include "bounce.h"

Bounce::Bounce(uint8_t buttonPin)
    : Action() {
        button = buttonPin;
}

void Bounce::start(Arduino_TFT *gfx) {
    gfx->fillScreen(WHITE);
    gfx->setCursor(10, 10);
    gfx->setTextColor(BLUE);
    gfx->println("Bounce V0.0.1");
}

void Bounce::loop(Arduino_TFT *gfx) {
    //gfx->fillScreen(WHITE);
}