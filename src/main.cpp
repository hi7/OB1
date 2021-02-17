#include <vector>
#include <string>
#include <sstream>
#include <Arduino_GFX_Library.h>
#include "OB1.h"
#include "controls.h"

const uint8_t BTN = 5;
std::vector<Button> actions;

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
    actions.push_back(Button(x,  y, min_width, "action I"));    y += LINE_HEIGHT;
    actions.push_back(Button(x,  y, min_width, "action II"));   y += LINE_HEIGHT;
    actions.push_back(Button(x,  y, min_width, "action III"));  y += LINE_HEIGHT;
    actions.push_back(Button(x,  y, min_width, "action IV"));   y += LINE_HEIGHT;
    actions.push_back(Button(x,  y, min_width, "action V"));    y += LINE_HEIGHT;
    actions.push_back(Button(x,  y, min_width, "action VI"));   y += LINE_HEIGHT;
    actions.push_back(Button(x,  y, min_width, "action VII"));  y += LINE_HEIGHT;
    actions.push_back(Button(x,  y, min_width, "action VIII")); y += LINE_HEIGHT;
    actions.push_back(Button(x,  y, min_width, "action IX"));   y += LINE_HEIGHT;
    actions.push_back(Button(x,  y, min_width, "action X"));    y += LINE_HEIGHT;
    actions.push_back(Button(x,  y, min_width, "action XI"));   y += LINE_HEIGHT;
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

void loop() {
    if(buttonPressed()) {
        drawControls();
    }
}
