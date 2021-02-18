#include "controls.h"
#include <Arduino_TFT.h>


class Bounce : public Action {
    public:
        void start(Arduino_TFT *gfx) override;
};