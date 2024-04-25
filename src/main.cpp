#include <Arduino.h>
#include "stemOSBoard.h"

Motor motor(Motor::PORTA_1, Motor::FORWARD);
stemWiFi wifi;
IMU imu;
Gamepad gamepad;


void update(void * arg) {
  while(1) {
    imu.calcule();
  }
}


void setup() {
  Serial.begin(115200);
  // wifi.configureWiFiAP();
  imu.init();
  xTaskCreatePinnedToCore(update, "IMU", 5000, NULL, 4, NULL, tskNO_AFFINITY);
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
    // esp_ipc_call(PRO_CPU_NUM, codeUser, NULL);
  }
}





