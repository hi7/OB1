#include "ob1.h"

Entity::Entity(const char* label, uint16_t posx, uint16_t posy, uint16_t foregroundColor) {
    name = label;
    x = posx;
    y = posy;
    color = foregroundColor;
}

uint16_t Entity::width() {
    return strlen(name) * 8;
}

void Level::draw(Arduino_TFT *gfx) {
    for(std::size_t i = 0; i < entities.size(); ++i) {
        Entity entity = entities.at(i);
        gfx->setCursor(entity.x, entity.y);
        gfx->setTextColor(RED, WHITE);
        gfx->println(entity.name);
    }
};

StartLevel::StartLevel() {
    entities.push_back(Entity("human", 10, 120, RED));
}

OB1::OB1(uint8_t buttonPin)
    : Action() {
        button = buttonPin;
        x = 160;
        y = 120;
        reciprocalSpeed = 10;
        level = new StartLevel();
}

void OB1::start(Arduino_TFT *gfx) {
    gfx->fillScreen(WHITE);
    log("OB1 V0.0.2", gfx);

    level->draw(gfx);
    draw(gfx);
}

int32_t i = 0;
void OB1::loop(Arduino_TFT *gfx) {
    uint16_t duration = millis() - lastUpdate;
    if(buttonDown() && (duration > reciprocalSpeed)) {
        draw(gfx);
        lastUpdate = millis();
    }
}

void OB1::draw(Arduino_TFT *gfx) {
    if(x > level->entities.at(0).width()) x -= 1;
    gfx->setCursor(x, y);
    gfx->setTextColor(BLACK, WHITE);
    gfx->println("OB1");
}