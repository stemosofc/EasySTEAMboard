#include "Digital.h"

// Construtor da classe Digital (recebe uma entrada)
Digital::Digital(PortasDigitais entrada) {
  signalPin = entrada;
  pinMode(signalPin, INPUT); 
}

// Retorna o Input da porta digital
bool Digital::getInput() {
  return digitalRead(signalPin);
}