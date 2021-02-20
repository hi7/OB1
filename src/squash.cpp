#include "squash.h"

Ball::Ball(uint16_t posx, uint16_t posy) {
    x = posx;
    y = posy;
    dx = -1;
    dy = 1;
    reciprocalSpeed = 5;
}
bool Ball::update(uint16_t playerY, uint16_t playerSize) {
    x += dx;
    y += dy;
    if(x > 303) {
        if(y > playerY - playerSize && y < playerY + playerSize) {
            dx = -dx;
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
    gfx->fillRect(x+3, y-5, 2, 10, WHITE);
}

Player::Player(uint16_t posy) {
    y = posy;
    size = 15;
    reciprocalSpeed = 4;
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

Squash::Squash(bool *menu) {
    exit = menu;
    player = new Player(120);
    ball = new Ball(304, 130);
    rounds = 11;
}

void Squash::drawRounds(Arduino_TFT *gfx) {
    gfx->fillRect(300, 10, 40, 10, WHITE);
    gfx->setCursor(300, 10);
    gfx->setTextColor(BLUE);
    gfx->println(rounds);
}

void Squash::drawField(Arduino_TFT *gfx) {
    gfx->fillRect(10,  25, 300, 2, RED);
    gfx->fillRect(10,  25, 2, 195, RED);
    gfx->fillRect(10,  220, 300, 2, RED);
}

void Squash::start(Arduino_TFT *gfx) {
    header("Squash V0.9", gfx);
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
            if(rounds == 0) {
                *exit = true;
            }
        }
    } else {
        uint16_t ballDuration = millis() - lastBallUpdate;
        if(ballDuration > ball->reciprocalSpeed) {
            bool out = ball->update(player->y, player->size);
            if(out && (ball->x > 325)) {
                ball->x = 304;
                ball->y = player->y;
                ball->dx = -1;
                rounds--;
                drawRounds(gfx);
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
