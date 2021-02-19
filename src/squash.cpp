#include "squash.h"

Ball::Ball(uint16_t posx, uint16_t posy) {
    x = posx;
    y = posy;
}
void Ball::draw(Arduino_TFT *gfx) {
    gfx->fillCircle(x, y, 4, BLUE);
}

Squash::Squash() {
    player = new Player(120);
    ball = new Ball(300, 120);
}

void drawField(Arduino_TFT *gfx) {
    gfx->fillRect(10,  25, 300, 2, RED);
    gfx->fillRect(10,  25, 2, 195, RED);
    gfx->fillRect(10,  220, 300, 2, RED);
}

Player::Player(uint16_t posy) {
    y = posy;
    size = 15;
}

void Player::up(Arduino_TFT *gfx) {
    if(y > 42) {
        y--;
        gfx->fillRect(310, y-size, 4, 4, BLACK);
        gfx->fillRect(310, y+size+4, 4, 4, WHITE);
    }
}
void Player::down(Arduino_TFT *gfx) {
    if(y < 204) {
        y++;
        gfx->fillRect(310, y-size-4, 4, 4, WHITE);
        gfx->fillRect(310, y+size-4, 4, 4, BLACK);
    }
}

void Player::draw(Arduino_TFT *gfx) {
    gfx->fillRect(310, y-size, 4, size>>2, BLACK);
}

void Squash::start(Arduino_TFT *gfx) {
    gfx->fillScreen(WHITE);
    log("Squash V0.0.1", gfx);
    drawField(gfx);
    player->draw(gfx);
    ball->draw(gfx);
}

unsigned long lastUpdate;
uint16_t reciprocalSpeed = 5;
void Squash::loop(Arduino_TFT *gfx) {
    uint16_t duration = millis() - lastUpdate;
    if(buttonDown() && (duration > reciprocalSpeed)) {
        player->up(gfx);
        lastUpdate = millis();
    } else if(duration > reciprocalSpeed) {
        player->down(gfx);
        lastUpdate = millis();
    }
}
