#include "grid.h"

void Grid::start(Arduino_TFT *gfx) {
    gfx->fillScreen(WHITE);
    gfx->setCursor(10, 10);
    gfx->setTextColor(BLUE);
    gfx->println("Grid V0.0.1");
}

void Grid::loop(Arduino_TFT *gfx) {
    //gfx->fillScreen(WHITE);
}