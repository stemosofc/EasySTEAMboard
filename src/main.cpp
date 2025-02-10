#include "EasySTEAM.h"

void setup() {
  Serial.begin(115200);
  easySTEAM.start();
}

void loop() {
  motor1.setPower(0.5);
}
