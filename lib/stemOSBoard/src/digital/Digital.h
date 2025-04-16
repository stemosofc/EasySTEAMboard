#ifndef DIGITAL_H
#define DIGITAL_H

#include "master.h"

// Enum das portas digitais para corresponder aos pinos
namespace Config_IO
{
  enum IOPorts {
    PORTA_1 = GPIO_NUM_34, 
    PORTA_2 = GPIO_NUM_35,
    PORTA_3 = GPIO_NUM_36,
    PORTA_4 = GPIO_NUM_39,
    PORTA_5 = GPIO_NUM_17
  };
}


class Digital {
  public:
    Digital(Config_IO::IOPorts entrada); // Construtor da classe Digital
    bool getInput(); // Obtém a entrada da porta digital
  private:
    int signalPin; // Pino de sinal
};

#endif