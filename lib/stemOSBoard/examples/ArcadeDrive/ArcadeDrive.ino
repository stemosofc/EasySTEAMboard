#include "Arara.h"

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

  motor1.setPower(frontLeftPower);
  motor2.setPower(backLeftPower);
}

