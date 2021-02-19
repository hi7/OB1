#include "controls.h"
#include <Arduino_TFT.h>

class Ball {
    uint16_t x, y;
    public:
        Ball(uint16_t posx, uint16_t posy);
        //void update(Arduino_TFT *gfx);
        void draw(Arduino_TFT *gfx);
};

class Squash : public Action {
    uint16_t y;
    Ball *ball;
    public:
        Squash();
        void start(Arduino_TFT *gfx) override;
        void loop(Arduino_TFT *gfx) override;
};