#include <Arduino.h>
#include "stemOSBoard.h"

Motor motor(Motor::PORTA_1, Motor::FORWARD);
stemWiFi wifi;

Gamepad gamepad;

void setup() {
  Serial.begin(115200);
  wifi.configureWiFiAP();
}

void codeUser(void * arg) {
  (void)arg;
  Serial.println("Teste");
  delay(50);
}

void loop() {
  if(wifi.state == "Habilitado") {
    estado = true;
  } else if (wifi.state == "Desabilitado") {
    estado = false;
  }
  if(estado) {
    esp_ipc_call(PRO_CPU_NUM, codeUser, NULL);
  }
}

