#ifndef EncoderESP_h
#define EncoderESP_h
#include "Arduino.h"
#include "ESP32Encoder.h"

// Classe wrapper de encoder
class Encoder {
  public:
    Encoder(int entrada); // Construtor da classe encoder
    Encoder(void); // Construtor vazio
    double getPosition(); // Obtém a posição do encoder
    void setPosition(int position); // Define a posição do encoder
    void setPositionFactor(double factor); // Define o fator de conversão do encoder
    void reset();
    ESP32Encoder encoder; // Objeto do encoder da bibilioteca
    static const int PORTA_1_ENCODER = 1;
    static const int PORTA_2_ENCODER = 2;
  private:
    int pinAEncoder; // Encoder pino A
    int pinBEncoder; // Encoder pino B
    double factor = 1; // variável que guarda o valor do fator de conversão
};
#endif