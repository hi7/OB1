#include "controls.h"
#include <Arduino_TFT.h>

class Morse : public Action {
    public:
        void start(Arduino_TFT *gfx) override;
        void loop(Arduino_TFT *gfx) override;
};