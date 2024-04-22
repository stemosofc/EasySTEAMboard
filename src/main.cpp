#include <Arduino.h>
#include "stemOSBoard.h"

Motor motor(Motor::PORTA_1, Motor::FORWARD);
stemWiFi wifi;

Gamepad gamepad;

void setup() {
  Serial.begin(115200);
  wifi.configureWiFiAP();
  gamepad.applyDeadband(0.02);
}

void loop() {
  double y = gamepad.getLeftAxisY();
  // motor.setPower(y);
}