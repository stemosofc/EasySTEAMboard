#include "EasySTEAM.h"

void setup() {
    Serial.begin(115200);
    easySTEAM.start();
}

void loop() {
    Serial.print("Encoder Position: ");
    Serial.println(motor1.encoder.getPosition());
}