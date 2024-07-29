#include "stemOSBoard.h"

void setup() {
  Arara.start();
}


void loop() {
  double y = gamepad.getLeftAxisY();
  double x = -gamepad.getRightAxisX();

  double powerLeft = y + x;
  double rightPower = y - x;

  double maxValue = max(abs(powerLeft), abs(rightPower));

  if(maxValue > 1) {
    powerLeft /= maxValue;
    rightPower /= maxValue;
  }

  motor1.setPower(-rightPower);
  motor2.setPower(powerLeft);
  motor3.setPower(-rightPower);
  motor4.setPower(powerLeft);
}


