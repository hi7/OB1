#include "controls.h"
#include <Arduino_TFT.h>

class Ball {
    public:
        uint16_t x, y;
        int dx, dy;
        uint8_t r, d;
        uint16_t reciprocalSpeed;
        Ball(uint16_t posx, uint16_t posy);
        bool update(uint16_t playerY, uint16_t playerSize);
        void draw(Arduino_TFT *gfx);
        void clear(Arduino_TFT *gfx);
};

class Player {
    public:
        uint16_t y;
        uint8_t size;
        uint16_t reciprocalSpeed;
        Player(uint16_t posy);
        void up(Arduino_TFT *gfx);
        void down(Arduino_TFT *gfx);
        void draw(Arduino_TFT *gfx);
};

class Squash : public Action {
    Player *player;
    Ball *ball;
    public:
        int8_t rounds;
        bool *exit;
        Squash(bool *menu);
        void drawField(Arduino_TFT *gfx);
        void drawRounds(Arduino_TFT *gfx);
        void start(Arduino_TFT *gfx) override;
        void loop(Arduino_TFT *gfx) override;
};