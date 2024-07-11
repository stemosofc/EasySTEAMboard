#include "stemOSboard.h"
stemWiFi wifi;

Gamepad gamepad;

Motor motorEsquerda(Motor::PORTA_1, Motor::REVERSE);
Motor motorDireita(Motor::PORTA_2, Motor::FORWARD);

void setup() {
  Serial.begin(115200);
  wifi.configureWiFiAP();
}

void loop() {
  if(estado) {
    float y = gamepad.getLeftAxisY();
    float turn = gamepad.getRightAxisX();

    double frontLeftPower = (y + turn);
    double backLeftPower = (y - turn);

    double maximum = max(abs(frontLeftPower), abs(backLeftPower));

    frontLeftPower /= maximum;
    backLeftPower /= maximum;

    motorEsquerda.setPower(frontLeftPower);
    motorDireita.setPower(backLeftPower);
  }
  if(wifi.state == "Habilitado") {
    estado = true;
  } else if(wifi.state == "Desabilitado") {
    estado = false;
  }
}

