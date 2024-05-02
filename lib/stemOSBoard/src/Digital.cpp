#include "Digital.h"

/**
 * @brief Cria um objeto da porta digital
 *
 * @param [in] entrada - define a entrada do sensor digital
 * @return N/A.
 */
Digital::Digital(PortasDigitais entrada) {
  signalPin = entrada;
  pinMode(signalPin, INPUT); 
}

/**
 * @brief Retorna o valor lido na porta digital
 *
 * @param [void]
 * @return bool.
 */
bool Digital::getInput() {
  return digitalRead(signalPin);
}