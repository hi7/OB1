#include "squash.h"

Ball::Ball(uint16_t posx, uint16_t posy) {
    x = posx;
    y = posy;
}
void Ball::draw(Arduino_TFT *gfx) {
    gfx->fillCircle(x, y, 4, BLUE);
}

Squash::Squash() {
    y = 120;
    ball = new Ball(300, 120);
}

void Squash::start(Arduino_TFT *gfx) {
    gfx->fillScreen(WHITE);
    log("Squash V0.0.2", gfx);
    gfx->fillRect(10,  25, 300, 2, RED);
    gfx->fillRect(10,  25, 2, 195, RED);
    gfx->fillRect(10,  220, 300, 2, RED);

    gfx->fillRect(310, y-10, 4, 20, BLACK);
    ball->draw(gfx);
}

void Squash::loop(Arduino_TFT *gfx) {
    //gfx->fillScreen(WHITE);
}
