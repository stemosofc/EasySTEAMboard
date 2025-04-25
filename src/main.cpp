#include "EasySTEAM.h"

void setup() {
  Serial.begin(115200);
  pinPoint.start();
}
void loop() {
  pinPoint.update();
  //Serial.printf("Device status: %d\n", pinPoint.getDeviceStatus());
  Serial.printf("Yaw: %f\n", pinPoint.getYaw());
  delay(50);
}