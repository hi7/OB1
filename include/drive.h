#include "controls.h"
#include <Arduino_TFT.h>

class Drive : public Action {
    bool *exit;
    public:
        Drive(bool *menu);
        void start(Arduino_TFT *gfx) override;
        void loop(Arduino_TFT *gfx) override;
};