#include "Arara.h"

void setup() {
    Serial.begin(115200);
    Arara.start();
}

void loop() {
    Serial.print("Encoder Position: ");
    Serial.println(motor1.encoder.getPosition());
}