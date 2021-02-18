#include <vector>
#include <string>
#include <sstream>
#include <Arduino_GFX_Library.h>
#include "OB1.h"
#include "bounce.h"
#include "squash.h"
#include "jump.h"
#include "grid.h"

const uint8_t BTN = 5;
std::vector<Button> actions;
Button *activeAction;

// set unconnected pins to OUTPUT to save energy
void saveEnergy() {
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(14, OUTPUT);
    pinMode(15, OUTPUT);
    pinMode(16, OUTPUT);
    pinMode(17, OUTPUT);
    pinMode(18, OUTPUT);
    pinMode(19, OUTPUT);
    pinMode(20, OUTPUT);
    pinMode(21, OUTPUT);
    pinMode(22, OUTPUT);
    pinMode(23, OUTPUT);
}

void drawControls() {
    for(std::size_t i = 0; i < actions.size(); ++i) {
      actions.at(i).draw(gfx);
    }
}

void setup(void) {
    saveEnergy();
    gfx->begin();
    gfx->fillScreen(WHITE);

#ifdef TFT_BL
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
    pinMode(BTN, INPUT);
#endif

    gfx->setCursor(10, 10);
    gfx->setTextColor(BLUE);
    gfx->println("OB1 V0.0.1");

    const u_int8_t LINE_HEIGHT = 20;
    const int16_t min_width = 75;
    const uint8_t x = 8;
    uint8_t y = 25;
    actions.push_back(Button(x, y, min_width, "bounce", new Bounce(BTN))); y += LINE_HEIGHT;
    actions.push_back(Button(x, y, min_width, "squash", new Squash())); y += LINE_HEIGHT;
    actions.push_back(Button(x, y, min_width, "jump",   new Jump())); y += LINE_HEIGHT;
    actions.push_back(Button(x, y, min_width, "grid",   new Grid())); y += LINE_HEIGHT;
    activeAction = &actions.at(0);
    activeAction->activate();
    drawControls();
}

int buttonState;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
const unsigned long DEBOUNCE_DELAY = 50;
bool buttonPressed() {
    bool result = false;
    int reading = digitalRead(BTN);
    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }
    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
        if (reading != buttonState) {
            buttonState = reading;
            if (buttonState == HIGH) {
                result = true;
            }
        }
    }
    lastButtonState = reading;
    return result;
}

bool menu = true;
void loop() {
    if(menu && buttonPressed()) {
        menu = false;
        activeAction->start(gfx);
    } else {
        activeAction->loop(gfx);
    }
}
