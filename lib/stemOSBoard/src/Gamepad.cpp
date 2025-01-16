#include "Gamepad.h"

JsonDocument Gamepad::gamepad;

Gamepad::Gamepad() {
  
}

/**
 * @brief Aplica um valor de deadband ao gamepad
 *
 * @param [void]
 * @return N/A.
 */
void Gamepad::applyDeadband(double deadband) {
  this->deadband = deadband;
}

/**
 * @brief Retorna o valor com a deadband aplicada
 *
 * @param [void]
 * @return double.
 */
double Gamepad::getValue(double value) {
  if(abs(value) > deadband) {
    if(maxMagnitude / deadband > 1.0e12) {
      return value > 0.0 ? value - deadband : value + deadband;
    }
    if(value > 0.0) {
      return maxMagnitude * (value - deadband) / (maxMagnitude - deadband);
    } else {
      return maxMagnitude * (value + deadband) / (maxMagnitude - deadband);
    }
  } else {
    return 0.0;
  }
}

/**
 * @brief Retorna o valor do eixo Y do analógico esquerdo
 *
 * @param [void]
 * @return double.
 */
double Gamepad::getLeftAxisY() {
  return getValue(Gamepad::gamepad["LY"]);
}

/**
 * @brief Retorna o valor do eixo X do analógico esquerdo
 *
 * @param [void]
 * @return double.
 */
double Gamepad::getLeftAxisX() {
  return getValue(Gamepad::gamepad["LX"]);
}

/**
 * @brief Retorna o valor do eixo Y do analógico direito
 *
 * @param [void]
 * @return double.
 */
double Gamepad::getRightAxisY() {
  return getValue(Gamepad::gamepad["RY"]);
}

/**
 * @brief Retorna o valor do eixo X do analógico direito
 *
 * @param [void]
 * @return double.
 */
// Obtém o eixo direita X do analógico
double Gamepad::getRightAxisX() {
  return getValue(Gamepad::gamepad["RX"]);
}

/**
 * @brief Retorna o valor do botão A
 *
 * @param [void]
 * @return bool.
 */
bool Gamepad::getButtonA() {
  return Gamepad::gamepad["A"];
}

/**
 * @brief Retorna o valor do botão B
 *
 * @param [void]
 * @return bool.
 */
bool Gamepad::getButtonB() {
  return Gamepad::gamepad["B"];
}

/**
 * @brief Retorna o valor do botão X
 *
 * @param [void]
 * @return bool.
 */
bool Gamepad::getButtonX() {
  return Gamepad::gamepad["X"];
}

/**
 * @brief Retorna o valor do botão Y
 *
 * @param [void]
 * @return bool.
 */
bool Gamepad::getButtonY() {
  return Gamepad::gamepad["Y"];
}

/**
 * @brief Retorna o valor do botão Right Bumper
 *
 * @param [void]
 * @return bool.
 */
bool Gamepad::getRightBumper() {
  return Gamepad::gamepad["RB"];
}

/**
 * @brief Retorna o valor do botão Left Bumper
 *
 * @param [void]
 * @return bool.
 */
bool Gamepad::getLeftBumper() {
  return Gamepad::gamepad["LB"];
}

/**
 * @brief Retorna o valor do botão Right Trigger
 *
 * @param [void]
 * @return double.
 */
double Gamepad::getRightTrigger() {
  return Gamepad::gamepad["RT"];
}

/**
 * @brief Retorna o valor do botão Right Trigger
 *
 * @param [void]
 * @return double.
 */
double Gamepad::getLeftTrigger() {
  return Gamepad::gamepad["LT"];
}

bool Gamepad::status() {
  return Gamepad::gamepad["EN"];
}


void Gamepad::reset() {
  const char * buttonsAndAxis[] = {"LT", "RT", "LB", "RB", "LY", "LX", "RX", "RY", "A", "B", "Y", "X"};
  
  for(int i = 0; i < (sizeof(buttonsAndAxis)/sizeof(char *)); i++) {
    Gamepad::gamepad[buttonsAndAxis[i]] = 0;
  }
}