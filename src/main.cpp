#include <Arduino.h>
#include "stemOSBoard.h"

Motor motor1(Motor::PORTA_1, Motor::FORWARD);
Motor motor2(Motor::PORTA_2, Motor::FORWARD);
Motor motor3(Motor::PORTA_3, Motor::FORWARD);
Motor motor4(Motor::PORTA_4, Motor::FORWARD);

stemWiFi wifi;
Gamepad gamepad;

void setup() {

}

void loop() {
  motor1.setPower(1.0);
  motor2.setPower(1.0);
  motor3.setPower(1.0);
  motor4.setPower(1.0);
}






