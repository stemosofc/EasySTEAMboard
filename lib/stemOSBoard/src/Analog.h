#ifndef ANALOG_H
#define ANALOH_H
#include "Arduino.h"

// Classe utilizada tanto para input como output de dispositivos analógicos

class Analog {
  public:
    Analog(void);  // Construtor da classe analógica
    int getAnalogInput();                             // Obtém uma entrada analógica do sensor acoplado
    void setAnalogOutput(int duty);                   // Define uma saída analógica
    static const int PORTA_ANALOGICA = 17;            // A única porta de servo na placa
    static const int SAIDA = 0;                       // Caso for utilizar a porta analógica para saída
    static const int ENTRADA = 1;                     // Caso for utilizar a porta analógica para entrada
  private:
};

#endif