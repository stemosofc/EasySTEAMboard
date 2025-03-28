#include "Digital.h"

/**
 * @brief Cria um objeto da porta digital
 *
 * @param [in] Porta a qual o sensor está conectado
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