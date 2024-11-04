#include "Arara.h"

void setup() {
    Arara.start();
}

void loop() {
    if(gamepad.getButtonA()) {
        servo1.setPosition(90);
    } else if (gamepad.getButtonB()) {
        servo1.setPosition(180);
    } else if (gamepad.getButtonX()) {
        servo1.setPosition(270);
    } else {
        servo1.setPosition(0);
    }
}