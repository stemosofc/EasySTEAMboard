#include "EasySTEAM.h"

void setup() {
  Serial.begin(115200);
  imu.start();
  colorSensor.start();
}
void loop() {
  Serial.printf("Yaw: %lf\n", imu.getYaw());
  Serial.printf("Roll: %lf\n", imu.getRoll());
  Serial.printf("Pitch: %lf\n", imu.getPitch());
  imu.calc();
  int x = encoder1.getPosition();
  int teste = encoder2.getPosition();
  colorSensor.getBlue();
}