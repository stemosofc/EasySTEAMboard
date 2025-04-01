#include "EasySTEAM.h"
#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  easySTEAM.start();
  //imu.init();
}
void loop() {
  if(!di1.getInput())
  {
    servo1.setPosition(270);
    servo2.setPosition(270);
    servo3.setPosition(270);

    motor1.setPower(1.0);
    motor2.setPower(1.0);
    motor3.setPower(1.0);
    motor4.setPower(1.0);

  } else if(!di2.getInput())
  {
    servo1.setPosition(180);
    servo2.setPosition(180);
    servo3.setPosition(180);

    motor1.setPower(0.8);
    motor2.setPower(0.8);
    motor3.setPower(0.8);
    motor4.setPower(0.8);

  } else if(!di3.getInput())
  {
    servo1.setPosition(90);
    servo2.setPosition(90);
    servo3.setPosition(90);

    motor1.setPower(0.6);
    motor2.setPower(0.6);
    motor3.setPower(0.6);
    motor4.setPower(0.6);

  } else if(!di4.getInput())
  {
    servo1.setPosition(45);
    servo2.setPosition(45);
    servo3.setPosition(45);

    motor1.setPower(0.2);
    motor2.setPower(0.2);
    motor3.setPower(0.2);
    motor4.setPower(0.2);

  } else if(!di5.getInput())
  {
    servo1.setPosition(0);
    servo2.setPosition(0);
    servo3.setPosition(0);

    motor1.setPower(0);
    motor2.setPower(0);
    motor3.setPower(0);
    motor4.setPower(0);
  }

  Serial.printf("Servo 1 position (DEG): %d\n", servo1.getPosition());
  Serial.printf("Encoder 1: %d\n", motor1.encoder.getPosition());
  Serial.printf("Encoder 2: %d\n", motor2.encoder.getPosition());
  //Serial.printf("Yaw: %d\n", imu.getYaw());
}