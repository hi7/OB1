#include "squash.h"

Ball::Ball(uint16_t posx, uint16_t posy) {
    x = posx;
    y = posy;
    dx = -1;
    dy = 1;
    r = 3;
    d = 6;
    reciprocalSpeed = 5;
}
bool Ball::update(uint16_t playerY, uint16_t playerSize) {
    x += dx;
    y += dy;
    if(x > 305) {
        if(y >= playerY - playerSize - d && y <= playerY + playerSize + d) {
            dx = -dx;
            if(y > playerY) dy = 1;
            if(y < playerY) dy = -1;
        } else return true;
    }
    if(x < 18) {
        dx = -dx;
    }
    if(y > 214 || y < 33) {
        dy = -dy;
    }
    return false; // ball is in game
}
void Ball::draw(Arduino_TFT *gfx) {
    gfx->fillRect(x-3, y-3, 6, 6, BLUE);
    gfx->drawPixel(x-3, y-3, WHITE);
    gfx->drawPixel(x-3, y+2, WHITE);
    gfx->drawPixel(x+2, y-3, WHITE);
    gfx->drawPixel(x+2, y+2, WHITE);
    gfx->fillRect(x-5, y-5, 10, 2, WHITE);
    gfx->fillRect(x-5, y+3, 10, 2, WHITE);
    gfx->fillRect(x-5, y-5, 2, 10, WHITE);
    if(x < 305) {
        gfx->fillRect(x+3, y-5, 2, 10, WHITE);
    }
}
void Ball::clear(Arduino_TFT *gfx) {
    gfx->fillRect(x-4, y-4, 8, 8, WHITE);
}

Player::Player(uint16_t posy) {
    y = posy;
    size = 15;
    reciprocalSpeed = 4;
}

void Player::up(Arduino_TFT *gfx) {
    if(y > 42) {
        y--;
        draw(gfx);
        gfx->fillRect(310, y-size, 4, 4, BLACK);
        gfx->fillRect(310, y+size, 4, size>>2, WHITE);
    }
}
void Player::down(Arduino_TFT *gfx) {
    if(y < 204) {
        y++;
        gfx->fillRect(310, y-size-4, 4, 4, WHITE);
        gfx->fillRect(310, y+size-4, 4, size>>2, BLACK);
    }
}

void Player::draw(Arduino_TFT *gfx) {
    gfx->fillRect(310, y-size, 4, size>>2, BLACK);
}

Squash::Squash(bool *menu) {
    exit = menu;
    player = new Player(120);
    ball = new Ball(304, 130);
    rounds = 7;
}

void Squash::drawRounds(Arduino_TFT *gfx) {
    gfx->fillRect(300, 10, 40, 10, WHITE);
    gfx->setCursor(300, 10);
    gfx->setTextColor(BLUE);
    gfx->println(rounds);
}

void Squash::drawField(Arduino_TFT *gfx) {
    gfx->fillRect(9, 24, 300, 3, RED);
    gfx->fillRect(9,  25, 3, 195, RED);
    gfx->fillRect(9, 220, 300, 3, RED);
}

void Squash::start(Arduino_TFT *gfx) {
    header("Squash V1.0", gfx);
    drawField(gfx);
    drawRounds(gfx);
    player->draw(gfx);
    ball->draw(gfx);
}

unsigned long lastBallUpdate;
unsigned long lastPlayerUpdate;
unsigned long wait = 0;
void Squash::loop(Arduino_TFT *gfx) {
    if(wait > 0) {
        if(wait < millis()) {
            wait = 0;
            ball->clear(gfx);
            ball->x = 304;
            ball->y = player->y;
            ball->dx = -1;
            rounds--;
            drawRounds(gfx);
            if(rounds == 0) {
                *exit = true;
            }
        }
    } else {
        uint16_t ballDuration = millis() - lastBallUpdate;
        if(ballDuration > ball->reciprocalSpeed) {
            bool out = ball->update(player->y, player->size);
            if(out) {
                wait = millis() + 330;
            }
            ball->draw(gfx);
            lastBallUpdate = millis();
        }
        uint16_t playerDuration = millis() - lastPlayerUpdate;
        if(playerDuration > player->reciprocalSpeed) {
            if(buttonDown()) {
                player->up(gfx);
                lastPlayerUpdate = millis();
            } else {
                player->down(gfx);
                lastPlayerUpdate = millis();
            }
        }
    }
}
