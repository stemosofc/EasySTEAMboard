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
  encoder2.getPosition();
  Serial.printf("Red: %d\n", colorSensor.getRed());
  Serial.printf("Blue: %d\n", colorSensor.getBlue());
  Serial.printf("Green: %d\n", colorSensor.getGreen());
  
}