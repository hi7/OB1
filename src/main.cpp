#include <vector>
#include <string>
#include <sstream>
#include <Arduino_GFX_Library.h>
#include "OB1.h"
#include "ob1.h"
#include "morse.h"
#include "squash.h"
#include "jump.h"
#include "grid.h"

bool menu = true;
bool menuVislible = true;
std::vector<Button> buttons;
size_t activeButtonIndex = 0;

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

void drawMenu() {
    if(!menuVislible) {
        gfx->fillScreen(WHITE);
        menuVislible = true;
    }
    log("OB1 V0.1", gfx);
    for(std::size_t i = 0; i < buttons.size(); ++i) {
      buttons.at(i).draw(gfx);
    }
}

Button* activeButton() {
    return &buttons.at(activeButtonIndex);
}

void activateButton(size_t index) {
    activeButtonIndex = index;
    for(std::size_t i = 0; i < buttons.size(); ++i) {
      buttons.at(i).deactivate();
    }
    activeButton()->activate();
}

void tearingEffectLine(uint8_t on) {
    bus->beginWrite();
    bus->writeCommand(ST7789_TEON);
    bus->write(on);
    bus->endWrite();
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

    const u_int8_t LINE_HEIGHT = 20;
    const int16_t min_width = 75;
    const uint8_t x = 8;
    uint8_t y = 25;
    buttons.push_back(Button(x, y, min_width, "squash", new Squash(&menu))); y += LINE_HEIGHT;
    buttons.push_back(Button(x, y, min_width, "OB1",    new OB1(BTN))); y += LINE_HEIGHT;
    buttons.push_back(Button(x, y, min_width, "morse",  new Morse()));  y += LINE_HEIGHT;
    buttons.push_back(Button(x, y, min_width, "jump",   new Jump()));   y += LINE_HEIGHT;
    buttons.push_back(Button(x, y, min_width, "grid",   new Grid()));   y += LINE_HEIGHT;
    activateButton(0);
    drawMenu();
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

bool pressed = false;
unsigned long startTime = 0;
unsigned long buttonReleased() {
    uint8_t reading = digitalRead(BTN);
    if(!pressed && (reading == HIGH)) {
        pressed = true;
        startTime = millis();
    }
    if(pressed && (reading == LOW)) {
        pressed = false;
        return millis() - startTime;
    } 
    
    return 0;
}

const unsigned long LONG_PRESS = 700;
void loop() {
    if(menu) {
        if(!menuVislible) {
            drawMenu();
        }
        if(pressed) {
            unsigned long duration = millis() - startTime;
            if(duration > LONG_PRESS) {
                if(activeButtonIndex < buttons.size() -1 ) {
                    activeButtonIndex++;
                } else {
                    activeButtonIndex = 0;
                }
                activateButton(activeButtonIndex);
                drawMenu();
                startTime = millis();
            }
        }

        unsigned long duration = buttonReleased();
        if(duration != 0) {
            if(duration < LONG_PRESS) {
                activeButton()->action()->start(gfx);
                menu = false;
                menuVislible = false;
            }
        }
    } else {
        activeButton()->action()->loop(gfx);
    }
}
