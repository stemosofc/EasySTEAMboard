#include "stemOSBoard.h"

Gamepad gamepad;

void setup() {
  wifi.configureWiFiAP();
}


void loop() {
  motor1.setPower(gamepad.getLeftAxisY());
  motor2.setPower(gamepad.getLeftAxisY());
  motor3.setPower(gamepad.getLeftAxisY());
  motor4.setPower(gamepad.getLeftAxisY());
}


