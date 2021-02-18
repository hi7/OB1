#include "squash.h"

void Squash::start(Arduino_TFT *gfx) {
    gfx->fillScreen(WHITE);
    gfx->setCursor(10, 10);
    gfx->setTextColor(BLUE);
    gfx->println("Squash V0.0.1");
}

void Squash::loop(Arduino_TFT *gfx) {
    //gfx->fillScreen(WHITE);
}
