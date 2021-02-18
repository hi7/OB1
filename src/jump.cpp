#include "jump.h"

void Jump::start(Arduino_TFT *gfx) {
    gfx->fillScreen(WHITE);
    gfx->setCursor(10, 10);
    gfx->setTextColor(BLUE);
    gfx->println("Jump V0.0.1");
}

void Jump::loop(Arduino_TFT *gfx) {
    //gfx->fillScreen(WHITE);
}