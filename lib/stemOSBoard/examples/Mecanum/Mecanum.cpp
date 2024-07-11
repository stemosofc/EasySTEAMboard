#include "stemOSboard.h"


// Use #define TELEOPERADO for teleop and AUTONOMO for autonomous

#define TELEOPERADO

stemWiFi wifi;

Gamepad gamepad;

Motor motorEsquerdaFrente(Motor::PORTA_1, Motor::REVERSE);
Motor motorEsquerdaTras(Motor::PORTA_2, Motor::REVERSE);
Motor motorDireitaFrente(Motor::PORTA_3, Motor::FORWARD);
Motor motorDireitaTras(Motor::PORTA_4, Motor::FORWARD);

void setup() {
  Serial.begin(115200);
  wifi.configureWiFiAP();

  delay(100);

  //esp_ipc_call(PRO_CPU_NUM, userCodeTeleopInit, NULL);
  estado = wifi.waitForStart();
  Serial.println(estado);
}

void loop() {
  if(estado) {
    float y = gamepad.getLeftAxisY();
    float x = gamepad.getLeftAxisX();
    float turn = gamepad.getRightAxisX();

    float denominator = max(abs(y) + abs(x) + abs(turn), 1.f);

    double frontLeftPower = (y + x + turn) / denominator;
    double backLeftPower = (y - x + turn) / denominator;
    double frontRightPower = (y - x - turn) / denominator;
    double backRightPower = (y + x - turn) / denominator;

    motorEsquerdaFrente.setPower(frontLeftPower);
    motorEsquerdaTras.setPower(backLeftPower);
    motorDireitaFrente.setPower(frontRightPower);
    motorDireitaTras.setPower(backRightPower);
  }
  if(wifi.state == "Habilitado") {
    estado = true;
  } else if(wifi.state == "Desabilitado") {
    estado = false;
  }
}

