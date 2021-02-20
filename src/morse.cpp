#include "morse.h"

Morse::Morse(bool *menu) {
    exit = menu;
    code.reserve(5);
    text = "";
}

void Morse::start(Arduino_TFT *gfx) {
    gfx->fillScreen(WHITE);
    gfx->setCursor(10, 10);
    gfx->setTextColor(BLUE);
    gfx->println("Morse V0.1");
}

char Morse::decode() {
    if(code.size() == 2 && !code.at(0) && code.at(1)) return 'a';
    if(code.size() == 4 && code.at(0) && !code.at(1) && !code.at(2) && !code.at(3)) return 'b';
    if(code.size() == 4 && code.at(0) && !code.at(1) && code.at(2) && !code.at(3)) return 'c';
    if(code.size() == 3 && code.at(0) && !code.at(1) && !code.at(2)) return 'd';
    if(code.size() == 1 && !code.at(0)) return 'e';
    if(code.size() == 4 && !code.at(0) && !code.at(1) && code.at(2) && !code.at(3)) return 'f';
    if(code.size() == 3 && code.at(0) && code.at(1) && !code.at(2)) return 'g';
    if(code.size() == 4 && !code.at(0) && !code.at(1) && !code.at(2) && !code.at(3)) return 'h';
    if(code.size() == 2 && !code.at(0) && !code.at(1)) return 'i';
    if(code.size() == 4 && !code.at(0) && code.at(1) && code.at(2) && code.at(3)) return 'j';
    if(code.size() == 3 && code.at(0) && !code.at(1) && code.at(2)) return 'k';
    if(code.size() == 4 && !code.at(0) && code.at(1) && !code.at(2) && !code.at(3)) return 'l';
    if(code.size() == 2 && code.at(0) && code.at(1)) return 'm';
    if(code.size() == 2 && code.at(0) && !code.at(1)) return 'n';
    if(code.size() == 3 && code.at(0) && code.at(1) && code.at(2)) return 'o';
    if(code.size() == 4 && !code.at(0) && code.at(1) && code.at(2) && !code.at(3)) return 'p';
    if(code.size() == 4 && code.at(0) && code.at(1) && !code.at(2) && code.at(3)) return 'p';
    if(code.size() == 3 && !code.at(0) && code.at(1) && !code.at(2)) return 'r';
    if(code.size() == 3 && !code.at(0) && !code.at(1) && !code.at(2)) return 's';
    if(code.size() == 1 && code.at(0)) return 't';
    if(code.size() == 3 && !code.at(0) && !code.at(1) && code.at(2)) return 'u';
    if(code.size() == 4 && !code.at(0) && !code.at(1) && !code.at(2) && code.at(3)) return 'v';
    if(code.size() == 3 && !code.at(0) && code.at(1) && code.at(2)) return 'w';
    if(code.size() == 4 && code.at(0) && !code.at(1) && !code.at(2) && code.at(3)) return 'x';
    if(code.size() == 4 && code.at(0) && !code.at(1) && code.at(2) && code.at(3)) return 'y';
    if(code.size() == 4 && code.at(0) && code.at(1) && !code.at(2) && !code.at(3)) return 'z';

    if(code.size() == 5 && !code.at(0) && code.at(1) && code.at(2) && code.at(3) && code.at(4)) return '1';
    if(code.size() == 5 && !code.at(0) && !code.at(1) && code.at(2) && code.at(3) && code.at(4)) return '2';
    if(code.size() == 5 && !code.at(0) && !code.at(1) && !code.at(2) && code.at(3) && code.at(4)) return '3';
    if(code.size() == 5 && !code.at(0) && !code.at(1) && !code.at(2) && !code.at(3) && code.at(4)) return '4';
    if(code.size() == 5 && !code.at(0) && !code.at(1) && !code.at(2) && !code.at(3) && !code.at(4)) return '5';
    if(code.size() == 5 && code.at(0) && !code.at(1) && !code.at(2) && !code.at(3) && !code.at(4)) return '6';
    if(code.size() == 5 && code.at(0) && code.at(1) && !code.at(2) && !code.at(3) && !code.at(4)) return '7';
    if(code.size() == 5 && code.at(0) && code.at(1) && code.at(2) && !code.at(3) && !code.at(4)) return '8';
    if(code.size() == 5 && code.at(0) && code.at(1) && code.at(2) && code.at(3) && !code.at(4)) return '9';
    if(code.size() == 5 && code.at(0) && code.at(1) && code.at(2) && code.at(3) && code.at(4)) return '0';
    return -1;
}

const uint16_t LONG = 200;
//const uint16_t BREAK = 500;
void Morse::loop(Arduino_TFT *gfx) {
    unsigned long duration = buttonReleased();
    if(duration > 0) {
        bool longImpulse = duration > LONG;
        logAt(longImpulse ? "long" : "short", 100, 10, gfx, true);
        code.push_back(longImpulse);
        logAt(code.size(), 140, 10, gfx, true);
        char c = decode();
        if(c != -1) {
            logAt(c, 160, 10, gfx, true);
            text += c;
            code.clear();
            logAt(text.c_str(), 190, 10, gfx, true);
        }
    }
    // *exit = true;
}