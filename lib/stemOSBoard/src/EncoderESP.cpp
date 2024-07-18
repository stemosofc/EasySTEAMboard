#include "EncoderESP.h"

/**
 * @brief Cria um objeto de Encoder
 *
 * @param [in] entrada - porta que o encoder está conectado
 * @return N/A.
 */
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
      log_e("Encoder não pode ser inicializado");
  }
   ESP32Encoder encoder;
   encoder.attachFullQuad(pinBEncoder, pinAEncoder);
   this->encoder = encoder;
}
EncoderESP::EncoderESP() {
  
}

/**
 * @brief Retorna a posição do encoder
 *
 * @param [void]
 * @return double.
 */
double EncoderESP::getPosition() {
  return encoder.getCount() * factor;
}

/**
 * @brief Define a posição do encoder
 *
 * @param [in] position - posição a ser definida
 * @return double.
 */
void EncoderESP::setPosition(int position) {
  encoder.setCount(position / factor);
}

/**
 * @brief Define o fator de conversão utilizado no cálculo do encoder
 *
 * @param [in] factor - define uma posição para o encoder
 * @return double.
 */
void EncoderESP::setPositionFactor(double factor) {
    this->factor = factor;
}