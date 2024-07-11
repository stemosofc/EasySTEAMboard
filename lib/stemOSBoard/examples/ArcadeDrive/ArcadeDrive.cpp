#include "stemOSboard.h"
stemWiFi wifi;

Gamepad gamepad;

Motor motorEsquerda(Motor::PORTA_1, Motor::REVERSE);
Motor motorDireita(Motor::PORTA_2, Motor::FORWARD);

void setup() {
  wifi.configureWiFiAP();
}

void loop() {
  float y = gamepad.getLeftAxisY();
  float turn = gamepad.getRightAxisX();

  double frontLeftPower = (y + turn);
  double backLeftPower = (y - turn);

  double maximum = max(abs(frontLeftPower), abs(backLeftPower));

  frontLeftPower /= maximum;
  backLeftPower /= maximum;

  motorEsquerda.setPower(frontLeftPower);
  motorDireita.setPower(backLeftPower);
}

