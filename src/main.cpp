#include "EasySTEAM.h"
#include <Arduino.h>

void setup() {
  easySTEAM.start();
}
void loop() {
  /*
  motor1.setPower(gamepad.getLeftAxisY());
  motor2.setPower(gamepad.getLeftAxisY());
  motor3.setPower(gamepad.getLeftAxisY());
  motor4.setPower(gamepad.getLeftAxisY());
  */
  servo1.setPosition(270);
  servo2.setPosition(270);
  servo3.setPosition(270);
  delay(1000);
  servo1.setPosition(180);
  servo2.setPosition(180);
  servo3.setPosition(180);
  delay(1000);
  servo1.setPosition(0);
  servo2.setPosition(0);
  servo3.setPosition(0);
  delay(1000);
}