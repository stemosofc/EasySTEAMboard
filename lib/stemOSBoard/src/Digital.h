#ifndef DIGITAL_H
#define DIGITAL_H
#include "Arduino.h"

// Enum das portas digitais para corresponder aos pinos
enum PortasDigitais {
  PORTA_1 = 34,
  PORTA_2 = 35,
  PORTA_3 = 36,
  PORTA_4 = 17,
  PORTA_5 = 39
};

class Digital {
  public:
    Digital(PortasDigitais entrada); // Construtor da classe Digital
    bool getInput(); // Obtém a entrada da porta digital
  private:
    int signalPin; // Pino de sinal
};

#endif