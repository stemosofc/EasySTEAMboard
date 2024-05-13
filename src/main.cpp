#include "stemOSboard.h"
stemWiFi wifi;

Gamepad gamepad;

Motor MotorEsquerdaFrente(Motor::PORTA_1, Motor::REVERSE);
Motor MotorDireitaTras(Motor::PORTA_2, Motor::FORWARD);
Motor MotorEsquerdaTras(Motor::PORTA_3, Motor::REVERSE);
Motor MotorDireitaFrente(Motor::PORTA_4, Motor::FORWARD);

void setup() {
  wifi.configureWiFiAP();
  gamepad.applyDeadband(0.02);
}

void loop() {
  double y = gamepad.getLeftAxisY();
  double x = -gamepad.getLeftAxisX();

  double powerLeft = y + x;
  double powerRight = y - x;

  MotorEsquerdaFrente.setPower(powerLeft);
  MotorEsquerdaTras.setPower(powerLeft);
  MotorDireitaFrente.setPower(powerRight);
  MotorDireitaTras.setPower(powerRight);
}

