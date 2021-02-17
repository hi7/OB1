#include <algorithm>
#include <Arduino_TFT.h>

class Button {
    uint16_t x, y, min_width;
    const char* label;
    public:
        Button(uint16_t x, uint16_t y, uint16_t minimal_width, const char* label);
        void draw(Arduino_TFT *gfx);
};