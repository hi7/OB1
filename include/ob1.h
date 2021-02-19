#include "controls.h"
#include <Arduino_TFT.h>

class OB1 : public Action {
    uint8_t button;
    uint16_t x, y;
    uint16_t reciprocalSpeed;
    unsigned long lastUpdate;
    public:
        OB1(uint8_t buttonPin);
        void start(Arduino_TFT *gfx) override;
        void loop(Arduino_TFT *gfx) override;
        void draw(Arduino_TFT *gfx);
};
