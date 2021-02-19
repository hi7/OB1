#include "ob1.h"

OB1::OB1(uint8_t buttonPin)
    : Action() {
        button = buttonPin;
        x = 160;
        y = 120;
        reciprocalSpeed = 10;
}

void OB1::start(Arduino_TFT *gfx) {
    gfx->fillScreen(WHITE);
    gfx->setCursor(10, 10);
    gfx->setTextColor(BLUE);
    gfx->println("OB1 V0.0.1");
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
    if(x > 20) x -= 1;
    gfx->setCursor(x, y);
    gfx->setTextColor(RED, WHITE);
    gfx->println("OB1");
}