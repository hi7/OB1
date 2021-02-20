#include "morse.h"

Morse::Morse(bool *menu) {
    exit = menu;
    code.reserve(6);
    text = "";
    offset = 0;
}

void Morse::start(Arduino_TFT *gfx) {
    header("Morse V1.0", gfx);
    drawChart(gfx);
}

void Morse::drawSignal(bool longImpulse, uint16_t x, uint16_t y, Arduino_TFT *gfx) {
    if(longImpulse) {
        gfx->fillRect(x+offset, y, 20, 10, BLACK);
        offset += 22;
    } else {
        gfx->fillCircle(x+6+offset, y+5, 5, BLACK);
        offset += 14;
    }
}


void Morse::drawCode(const char *s, std::vector<bool> code, uint16_t x, uint16_t y, Arduino_TFT *gfx) {
    gfx->setCursor(x, y+2);
    gfx->setTextColor(BLACK);
    gfx->println(s);
    for(std::size_t i = 0; i < code.size(); ++i) {
        drawSignal(code.at(i), x + 10, y, gfx);
    }
    offset = 0;
}

void Morse::drawChart(Arduino_TFT *gfx) {
    drawCode("A", {false, true}, 10, 100, gfx);
    drawCode("B", {true, false, false, false}, 10, 115, gfx);
    drawCode("C", {true, false, true, false}, 10, 130, gfx);
    drawCode("D", {true, false, false}, 10, 145, gfx);
    drawCode("E", {false}, 10, 160, gfx);
    drawCode("F", {false, false, true, false}, 10, 175, gfx);
    drawCode("G", {true, true, false}, 10, 190, gfx);
    drawCode("H", {false, false, false, false}, 10, 205, gfx);
    drawCode("I", {false, false}, 10, 220, gfx);

    drawCode("J", {false, true, true, true}, 100, 100, gfx);
    drawCode("K", {true, false, true}, 100, 115, gfx);
    drawCode("L", {false, true, false, false}, 100, 130, gfx);
    drawCode("M", {true, true}, 100, 145, gfx);
    drawCode("N", {true, false}, 100, 160, gfx);
    drawCode("O", {true, true, true}, 100, 175, gfx);
    drawCode("P", {false, true, true, false}, 100, 190, gfx);
    drawCode("Q", {true, true, false, true}, 100, 205, gfx);
    drawCode("R", {false, true, false}, 100, 220, gfx);

    drawCode("S", {false, false, false}, 210, 100, gfx);
    drawCode("T", {true}, 210, 115, gfx);
    drawCode("U", {false, false, true}, 210, 130, gfx);
    drawCode("V", {false, false, false, true}, 210, 145, gfx);
    drawCode("W", {false, true, true}, 210, 160, gfx);
    drawCode("X", {true, false, false, true}, 210, 175, gfx);
    drawCode("Y", {true, false, true, true}, 210, 190, gfx);
    drawCode("Z", {true, true, false, false}, 210, 205, gfx);
    //offset = 10;
    //drawCode("OUT", {false, true, false, true, false}, 198, 220, gfx);
    offset = 0;
}

char Morse::decode() {
    // OUT: exit code
    if(code.size() == 5 && !code.at(0) && code.at(1) && !code.at(2) && code.at(3) && !code.at(4)) return -2;

    if(code.size() == 2 && !code.at(0) && code.at(1)) return 'A';
    if(code.size() == 4 && code.at(0) && !code.at(1) && !code.at(2) && !code.at(3)) return 'B';
    if(code.size() == 4 && code.at(0) && !code.at(1) && code.at(2) && !code.at(3)) return 'C';
    if(code.size() == 3 && code.at(0) && !code.at(1) && !code.at(2)) return 'D';
    if(code.size() == 1 && !code.at(0)) return 'E';
    if(code.size() == 4 && !code.at(0) && !code.at(1) && code.at(2) && !code.at(3)) return 'F';
    if(code.size() == 3 && code.at(0) && code.at(1) && !code.at(2)) return 'G';
    if(code.size() == 4 && !code.at(0) && !code.at(1) && !code.at(2) && !code.at(3)) return 'H';
    if(code.size() == 2 && !code.at(0) && !code.at(1)) return 'I';
    if(code.size() == 4 && !code.at(0) && code.at(1) && code.at(2) && code.at(3)) return 'J';
    if(code.size() == 3 && code.at(0) && !code.at(1) && code.at(2)) return 'K';
    if(code.size() == 4 && !code.at(0) && code.at(1) && !code.at(2) && !code.at(3)) return 'L';
    if(code.size() == 2 && code.at(0) && code.at(1)) return 'M';
    if(code.size() == 2 && code.at(0) && !code.at(1)) return 'N';
    if(code.size() == 3 && code.at(0) && code.at(1) && code.at(2)) return 'O';
    if(code.size() == 4 && !code.at(0) && code.at(1) && code.at(2) && !code.at(3)) return 'P';
    if(code.size() == 4 && code.at(0) && code.at(1) && !code.at(2) && code.at(3)) return 'Q';
    if(code.size() == 3 && !code.at(0) && code.at(1) && !code.at(2)) return 'R';
    if(code.size() == 3 && !code.at(0) && !code.at(1) && !code.at(2)) return 'S';
    if(code.size() == 1 && code.at(0)) return 'T';
    if(code.size() == 3 && !code.at(0) && !code.at(1) && code.at(2)) return 'U';
    if(code.size() == 4 && !code.at(0) && !code.at(1) && !code.at(2) && code.at(3)) return 'V';
    if(code.size() == 3 && !code.at(0) && code.at(1) && code.at(2)) return 'W';
    if(code.size() == 4 && code.at(0) && !code.at(1) && !code.at(2) && code.at(3)) return 'X';
    if(code.size() == 4 && code.at(0) && !code.at(1) && code.at(2) && code.at(3)) return 'Y';
    if(code.size() == 4 && code.at(0) && code.at(1) && !code.at(2) && !code.at(3)) return 'Z';

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
const uint16_t BREAK = 700;
const uint16_t NEW_WORD = 1600;
uint32_t lastSignal = 0xffffffff;
void Morse::loop(Arduino_TFT *gfx) {
    if(code.size() > 0 && millis() > (lastSignal + BREAK)) {
        char c = decode();
        if(c == -2) {
            logAt("OUT!!!", 140, 10, gfx, false);
            *exit = true;
            //return; // exit method
        }
        if(c >= 0) {
            text += c;
            logAt(text.c_str(), 10, 42, gfx, true);
            //gfx->fillRect(100, 10, 140, 10, WHITE); // clear long/short hint
            gfx->fillRect(10, 25, 310, 13, WHITE); // clear dots & strokes
        }
        code.clear();
        offset = 0;
    }
    unsigned long duration = buttonReleased();
    if(duration > 0) {
        if(text.size() > 0 && millis() > lastSignal + NEW_WORD) {
            text += ' ';
        }
        bool longImpulse = duration > LONG;
        drawSignal(longImpulse, 10, 25, gfx);
        //logAt(longImpulse ? "long" : "short", 100, 10, gfx, true);
        code.push_back(longImpulse);
        lastSignal = millis();
    }
}