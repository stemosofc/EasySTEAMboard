#include "Gamepad.h"

JsonDocument Gamepad::gamepad;

void Gamepad::applyDeadband(double deadband) {
  this->deadband = deadband;
}

double Gamepad::returnValueWithDeadband(double value) {
  if(abs(value) < abs(deadband)) {
    return .0;
  } else {
    return value;
  }
}
// Obtém o eixo esquerda Y do analógico
double Gamepad::getLeftAxisY() {
 return returnValueWithDeadband(Gamepad::gamepad["LY"]);
}

// Obtém o eixo esquerda X do analógico
double Gamepad::getLeftAxisX() {
  return Gamepad::gamepad["LX"];
}

// Obtém o eixo direita Y do analógico
double Gamepad::getRightAxisY() {
  return Gamepad::gamepad["RY"];
}

// Obtém o eixo direita X do analógico
double Gamepad::getRightAxisX() {
  return Gamepad::gamepad["RX"];
}

// Retorna o botão A do gamepad
bool Gamepad::getButtonA() {
  return Gamepad::gamepad["A"];
}

// Retorna o botão B do gamepad
bool Gamepad::getButtonB() {
  return Gamepad::gamepad["B"];
}

// Retorna o botão X do gamepad
bool Gamepad::getButtonX() {
  return Gamepad::gamepad["X"];
}

// Retorna o botão Y do gamepad
bool Gamepad::getButtonY() {
  return Gamepad::gamepad["Y"];
}

// Retorna o bumper direito do gamepad
bool Gamepad::getRightBumper() {
  return Gamepad::gamepad["RB"];
}

// Retorna o bumper esquerdo do gamepad
bool Gamepad::getLeftBumper() {
  return Gamepad::gamepad["LB"];
}

// Retorna o trigger direito do gamepad
double Gamepad::getRightTrigger() {
  return Gamepad::gamepad["RT"];
}

// Retorna o trigger esquerdo do gamepad
double Gamepad::getLeftTrigger() {
  return Gamepad::gamepad["LT"];
}