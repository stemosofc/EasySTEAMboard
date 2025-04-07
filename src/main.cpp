#include "EasySTEAM.h"
#include <Arduino.h>

void setup() {
  Serial.begin(115200);
}
void loop() {
  Serial.printf("Encoder 1: %lf\n", motor1.encoder.getPosition());
}