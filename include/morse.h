#include <string>
#include <vector>
#include "controls.h"
#include <Arduino_TFT.h>

class Morse : public Action {
    bool *exit;
    public:
        std::vector<bool> code;
        std::string text;
        uint16_t offset;
        Morse(bool *menu);
        char decode();
        void drawSignal(bool longImpule, uint16_t x, uint16_t y, Arduino_TFT *gfx);
        void drawCode(const char *s, std::vector<bool> code, uint16_t x, uint16_t y, Arduino_TFT *gfx);
        void drawChart(Arduino_TFT *gfx);
        void start(Arduino_TFT *gfx) override;
        void loop(Arduino_TFT *gfx) override;
};