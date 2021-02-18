#include "controls.h"
#include <Arduino_TFT.h>


class Bounce : public Action {
    uint8_t button;
    public:
        Bounce(uint8_t buttonPin);
        void start(Arduino_TFT *gfx) override;
        void loop(Arduino_TFT *gfx) override;
};
