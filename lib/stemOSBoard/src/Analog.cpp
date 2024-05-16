#include "Analog.h"

/**
 * @brief Cria um objeto da porta analógica
 *
 * @param [in] entrada - define a entrada do sensor analógico
 * @param [in] sensorType - saída ou entrada de dadoss
 * @return N/A.
 */
Analog::Analog() {
 
}


/**
 * @brief Retorna o valor lido pela entrada analógica
 *
 * @param [void]
 * @return int.
 */
int Analog::getAnalogInput() {
  return analogRead(Analog::PORTA_ANALOGICA);
}

/**
 * @brief Define uma saída analógica
 *
 * @param [in] duty - valor da saída [0, 1023]
 * @return N/A.
 */
void Analog::setAnalogOutput(int duty) {
  analogWrite(Analog::PORTA_ANALOGICA, duty);
}