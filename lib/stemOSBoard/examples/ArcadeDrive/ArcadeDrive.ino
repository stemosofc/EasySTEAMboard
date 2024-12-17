#include "EasySTEAM.h"

void setup() {
  easySTEAM.start();
  Serial.begin(115200);
}

void loop() {
    float y = gamepad.getLeftAxisY();
    float turn = gamepad.getRightAxisX();

    double frontLeftPower = (y + turn);
    double backLeftPower = (y - turn);

    double maximum = max(abs(frontLeftPower), abs(backLeftPower));
    if(maximum > 1) {
        frontLeftPower /= maximum;
        backLeftPower /= maximum;
    }
    
    motor1.setPower(-frontLeftPower);
    motor2.setPower(backLeftPower);
}

