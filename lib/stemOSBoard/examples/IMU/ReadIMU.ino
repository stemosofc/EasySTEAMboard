#include "Arara.h"

void setup() {
    Serial.begin(115200);
    Arara.start();
    imu.init();
}

void loop() {
    Serial.print("Yaw: ");
    Serial.println(imu.getYaw());
    Serial.print("Roll: ");
    Serial.println(imu.getRoll());
    Serial.print("Pitch: ");
    Serial.println(imu.getPitch());
}