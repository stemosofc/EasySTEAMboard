#include "Servo.h"

/**
 * @brief Cria um objeto de Servo
 *
 * @param [in] entrada a porta na qual o servo esta conectado
 * @return N/A.
 */
Servo::Servo(PortaServo entrada) {
  switch(entrada) {
    case PortaServo::PORTA_1_SERVO:
      channel = 8;
      break;
    case PortaServo::PORTA_2_SERVO:
      channel = 9;
      break;
    case PortaServo::PORTA_3_SERVO: 
      channel = 10;
      break;
  }
  ledcSetup(channel, Servo::FREQUENCY, Servo::RESOLUTION);
  ledcAttachPin(entrada, channel);
}

/**
 * @brief Cria um objeto de Servo
 *
 * @param [in] position define a posição do servo
 * @return N/A.
 */
void Servo::setPosition(float position) {
  position = max(-1.f, min(1.f, position));
  position = map(position, -1.f, 1.f, 0.f, 255.f);
  ledcWrite(channel, position);
}
