#include "EasySTEAM.h"
#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  easySTEAM.start();
}
void loop() {
  servo1.setPosition(270);
  Serial.printf("Servo 1: %d\n", servo1.getPosition());
  motor1.setPower(1.0);
  delay(1000);
  servo1.setPosition(0);
  servo3.setPosition(180);
  Serial.printf("Servo 1: %d\n", servo1.getPosition());
  delay(1000);
}