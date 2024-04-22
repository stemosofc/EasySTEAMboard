#include "stemOSboard.h"


// Use #define TELEOPERADO for teleop and AUTONOMO for autonomous

#define TELEOPERADO

stemWiFi wifi;

Gamepad gamepad;

Motor motorEsquerdaFrente(Motor::PORTA_1, Motor::REVERSE);
Motor motorEsquerdaTras(Motor::PORTA_2, Motor::REVERSE);

void setup() {
  Serial.begin(115200);
  wifi.configureWiFiAP();

  delay(100);

  estado = wifi.waitForStart();
  Serial.println(estado);
}

void loop() {
  String stat = wifi.getEnable();

  #ifdef TELEOPERADO
    wifi.getGamepadValues();
  #endif

  if(estado) {
   Serial.print("Posicao Encoder: ");
   Serial.println(motorEsquerdaFrente.encoderESP.getPosition());
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
