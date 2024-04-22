#include "Analog.h"

// Configura a porta analógica como INPUT ou OUTPUT
Analog::Analog(const int entrada, const int sensorType) {
  if (sensorType == Analog::SAIDA) {
    pinMode(Analog::PORTA_ANALOGICA, OUTPUT);
  } else {
    pinMode(Analog::PORTA_ANALOGICA, INPUT);
  }
}


// Retorna uma leitura analógica na porta indicada
int Analog::getAnalogInput() {
  return analogRead(Analog::PORTA_ANALOGICA);
}

// Define uma saída analógica (PWM) na porta indicada
void Analog::setAnalogOutput(int duty) {
  analogWrite(Analog::PORTA_ANALOGICA, duty);
}