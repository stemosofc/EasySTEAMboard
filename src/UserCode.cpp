#include "UserCode.h"

Motor motor(Motor::PORTA_1, Motor::FORWARD);
Gamepad gamepad;
void UserClass::init() {
    //Serial.println("Iniciou");
}

void UserClass::loop() {
    motor.setPower(0.3);
    //Serial.println(gamepad.getLeftAxisY());
}
