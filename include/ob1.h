#include "controls.h"
#include <vector>
#include <Arduino_TFT.h>

class Entity {
    public:
        const char* name;
        uint16_t x, y;
        uint16_t color;
        Entity(const char* label, uint16_t x, uint16_t y, uint16_t foregroundColor);
        uint16_t width();
};

class Level {
    public:
        std::vector<Entity> entities;
        void draw(Arduino_TFT *gfx);
};

class OB1 : public Action {
    uint8_t button;
    uint16_t x, y;
    uint16_t reciprocalSpeed;
    unsigned long lastUpdate;
    Level *level;
    public:
        OB1(uint8_t buttonPin);
        void start(Arduino_TFT *gfx) override;
        void loop(Arduino_TFT *gfx) override;
        void draw(Arduino_TFT *gfx);
};

class StartLevel : public Level {
    public:
        StartLevel();
};