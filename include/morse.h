#include "controls.h"
#include <Arduino_TFT.h>

class Morse : public Action {
    bool *exit;
    public:
        Morse(bool *menu);
        void start(Arduino_TFT *gfx) override;
        void loop(Arduino_TFT *gfx) override;
};