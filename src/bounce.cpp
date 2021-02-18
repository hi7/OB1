#include "bounce.h"

Bounce::Bounce(uint8_t buttonPin)
    : Action() {
        button = buttonPin;
}

void Bounce::start(Arduino_TFT *gfx) {
    gfx->fillScreen(WHITE);
    gfx->setCursor(10, 10);
    gfx->setTextColor(BLUE);
    gfx->println("Bounce V0.0.1");
}

int32_t i = 0;
void Bounce::loop(Arduino_TFT *gfx) {
    /*gfx->fillRect(10, 10, 60, 10, WHITE);
    gfx->setCursor(10, 10);
    gfx->setTextColor(RED);
    gfx->println(i);*/
    uint8_t reading = digitalRead(button);
    uint16_t color = reading == HIGH ? BLACK : WHITE;
    gfx->drawPixel(i % 320, (int32_t)i / 320, color);
    i++;
    if(i>75000) i = 0;
}