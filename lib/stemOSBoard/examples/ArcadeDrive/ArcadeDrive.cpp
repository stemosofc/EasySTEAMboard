#include "stemOSboard.h"

void setup() {
  Arara.start();
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

