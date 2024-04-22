#include "EncoderESP.h"

// Classe de encoder
EncoderESP::EncoderESP(int entrada) {
  switch(entrada) {
    case PORTA_1_ENCODER:
      pinAEncoder = 5;
      pinBEncoder = 14;
      break;
    case PORTA_2_ENCODER:
      pinAEncoder = 15;
      pinBEncoder = 16;
      break;
    default:
      if(Serial) {
        Serial.println("Encoder não pode ser inicializado");
      }
  }
   ESP32Encoder encoder;
   encoder.attachFullQuad(pinBEncoder, pinAEncoder);
   this->encoder = encoder;
}
EncoderESP::EncoderESP() {
  
}

// Obtém da posição do encoder
double EncoderESP::getPosition() {
  return encoder.getCount() * factor;
}

// Define a posição do encoder
void EncoderESP::setPosition(int position) {
  encoder.setCount(position / factor);
}

// Define o fator de conversão do encoder
void EncoderESP::setPositionFactor(double factor) {
    this->factor = factor;
}

// Atualiza o encoder para obter a nova posição
void EncoderESP::update() {
  // encoder.tick();
}