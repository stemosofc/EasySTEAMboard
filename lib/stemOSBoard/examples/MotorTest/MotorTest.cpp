#include "stemOSboard.h"


// Use #define TELEOPERADO for teleop and AUTONOMO for autonomous

#define TELEOPERADO

stemWiFi wifi;

Gamepad gamepad;

Motor motorEsquerdaFrente(Motor::PORTA_1, Motor::REVERSE);

void setup() {
  Serial.begin(115200);
  wifi.configureWiFiAP();

  delay(100);

  estado = wifi.waitForStart();
  log_i("Estado: ", estado);
}

void loop() {
  String stat = wifi.getEnable();

  if(estado and wifi.getClientConnected()) {
    for(int i = 0; i <= 1; i++) {
        Serial.print("Potência do motor: ");
        Serial.println(i);
        motorEsquerdaFrente.setPower(i);
    }
  }
  if(stat == "Habilitado") {
    estado = true;
  } else if(stat == "Desabilitado") {
    estado = false;
  }
}

// =============================================
//          CÓDIGO-DO-USUÁRIO ABAIXO
// =============================================


void userCodeTeleopInit(void * arg) {
  // Código do usuário que precisar ser inicializado
}
