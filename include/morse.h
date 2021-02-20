#include <string>
#include <vector>
#include "controls.h"
#include <Arduino_TFT.h>

class Morse : public Action {
    bool *exit;
    public:
        std::vector<bool> code;
        std::string text;
        Morse(bool *menu);
        char decode();
        void start(Arduino_TFT *gfx) override;
        void loop(Arduino_TFT *gfx) override;
};