#include "Digital.h"

// Construtor da classe Digital (recebe uma entrada)
Digital::Digital(PortasDigitais entrada) {
  signalPin = entrada;
  pinMode(signalPin, INPUT); 
}

// Retorna o Input da porta digital aa
bool Digital::getInput() {
  return digitalRead(signalPin);
}