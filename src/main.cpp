#include "EasySTEAM.h"

void setup() {
  Serial.begin(115200);
  easySTEAM.start();
  motor2.setPower(0.1);
}

void loop() {
  Serial.println(motor2.encoder.getPosition());
}