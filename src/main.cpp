#include "stemOSboard.h"
stemWiFi wifi;

Gamepad gamepad;

ServoOS servo(PortaServo::PORTA_1_SERVO);

void setup() {
  Serial.begin(115200);
  wifi.configureWiFiAP();
}

void loop() {
  delay(2000);
  for(double i = 135; i > 0; i -= 1) {
    servo.setSpeed(i);
    Serial.println(i);
    delay(10);
  }
  delay(2000);
    for(double i = 135; i < 270; i += 1) {
    servo.setSpeed(i);
    Serial.println(i);
    delay(10);
  }
  delay(2000);
}

