#include "morse.h"

void Morse::start(Arduino_TFT *gfx) {
    gfx->fillScreen(WHITE);
    gfx->setCursor(10, 10);
    gfx->setTextColor(BLUE);
    gfx->println("Morse V0.0.1");
}

void Morse::loop(Arduino_TFT *gfx) {
    //gfx->fillScreen(WHITE);
}