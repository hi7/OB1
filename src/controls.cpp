#include "controls.h"

void Action::header(const char* name, Arduino_TFT *gfx) {
    gfx->fillScreen(WHITE);
    gfx->setCursor(10, 10);
    gfx->setTextColor(BLUE);
    gfx->println(name);
}

Button::Button(uint16_t posx, uint16_t posy, uint16_t minimal_width, const char* text, Action *action) {
    x = posx;
    y = posy;
    min_width = minimal_width;
    label = text;
    _action = action;
    active = false;
}

uint16_t Button::width(uint16_t actual) {
    return std::max(actual, min_width);
}

Action* Button::action() {
    return _action;
}

void Button::activate() {
    active = true;
}
void Button::deactivate() {
    active = false;
}

void Button::draw(Arduino_TFT *gfx) {
    const uint16_t BORDER = 5;
    const uint16_t label_width = 6*strlen(label)+BORDER*2;
    gfx->fillRect(x-3, y-3, width(label_width)+3, 16, WHITE);
    if(active) {
        gfx->fillRoundRect(x-3, y-3, width(label_width)+3, 16, 8, 0x07E0);
    } else {
        gfx->fillRoundRect(x-2, y, width(label_width), 12, 6, 0xDFFC);
    }
    gfx->setCursor(x+BORDER, y+1);
    gfx->setTextColor(BLACK);
    gfx->println(label);
}

bool buttonDown() {
    return digitalRead(BTN) == HIGH;
}

bool buttonUp() {
    return digitalRead(BTN) == LOW;
}

bool pressed = false;
bool isPressed() {
    return pressed;
}

unsigned long startTime = 0;
unsigned long getStartTime() {
    return startTime;
}
void setStartTime(unsigned long time) {
    startTime = time;
}
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
void initLog(uint16_t x, uint16_t y, Arduino_TFT *gfx, bool clear) {
    if(clear) gfx->fillRect(x, y, 40, 10, WHITE);
    gfx->setCursor(x, y);
    gfx->setTextColor(BLUE);
}
void logAt(uint32_t i, uint16_t x, uint16_t y, Arduino_TFT *gfx, bool clear) {
    initLog(x, y, gfx, clear);
    gfx->println(i);
}
void logAt(size_t i, uint16_t x, uint16_t y, Arduino_TFT *gfx, bool clear) {
    initLog(x, y, gfx, clear);
    gfx->println(i);
}
void logAt(const char c, uint16_t x, uint16_t y, Arduino_TFT *gfx, bool clear) {
    initLog(x, y, gfx, clear);
    gfx->println(c);
}
void logAt(const char s[], uint16_t x, uint16_t y, Arduino_TFT *gfx, bool clear) {
    initLog(x, y, gfx, clear);
    gfx->println(s);
}
void logAt(char s[], uint16_t x, uint16_t y, Arduino_TFT *gfx, bool clear) {
    initLog(x, y, gfx, clear);
    gfx->println(s);
}
void log(const char s[], Arduino_TFT *gfx) {
    logAt(s, 10, 10, gfx, true);
}
void log(char s[], Arduino_TFT *gfx) {
    logAt(s, 10, 10, gfx, true);
}
void log(size_t n, Arduino_TFT *gfx) {
    initLog(110, 10, gfx, true);
    gfx->println(n);
}
void log(int8_t n, Arduino_TFT *gfx) {
    initLog(110, 10, gfx, true);
    gfx->println(n);
}
