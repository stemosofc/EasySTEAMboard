#include "Arara.h"

void setup() {
    Arara.start();
    Serial.begin(115200);
}

void loop() {
    if(di1.getInput()) {
        servo1.setPosition(90);
    } else if (di2.getInput()) {
        servo1.setPosition(180);
    } else if (di3.getInput()) {
        servo1.setPosition(270);
    } else {
        servo1.setPosition(0);
    }
}