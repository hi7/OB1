#include "drive.h"

Drive::Drive(bool *menu) {
    exit = menu;
}

void Drive::start(Arduino_TFT *gfx) {
    header("Drive V0.0.1", gfx);
    
}

void Drive::loop(Arduino_TFT *gfx) {
}