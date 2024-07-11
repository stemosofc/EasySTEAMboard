#include "stemOSboard.h"
stemWiFi wifi;

Gamepad gamepad;

Motor motorEsquerda(Motor::PORTA_1, Motor::REVERSE);
Motor motorDireita(Motor::PORTA_2, Motor::FORWARD);

void setup() {
  wifi.configureWiFiAP();
}

void loop() {
  double y = -gamepad.getLeftAxisY();
  double x = gamepad.getLeftAxisX();

  double powerLeft = y + x;
  double powerRight = y - x;
  
  motorEsquerda.setPower(powerLeft);
  motorDireita.setPower(powerRight);
}

