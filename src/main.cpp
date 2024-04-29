#include <Arduino.h>
#include "stemOSBoard.h"

Motor motor(Motor::PORTA_1, Motor::FORWARD);
stemWiFi wifi;
IMU imu;
Gamepad gamepad;

void setup() {
  Serial.begin(115200);
  wifi.configureWiFiAP();
  imu.init();
}

void loop() {
 Serial.println(imu.getYaw());
}


void enable() {
  if(wifi.state == "Habilitado") {
    estado = true;
  } else if (wifi.state == "Desabilitado") {
    estado = false;
  }
  if(estado) {
    double y = gamepad.getLeftAxisY();
    Serial.println(y);
    motor.setPower(y);
  }
}





