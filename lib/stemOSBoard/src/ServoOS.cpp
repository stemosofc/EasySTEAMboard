#include "ServoOS.h"

/**
 * @brief Cria um objeto de Servo
 *
 * @param [in] entrada a porta na qual o servo esta conectado
 * @return N/A.
 */
ServoOS::ServoOS(PortaServo entrada) {
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
  servo.attach(entrada, channel, 0, 270, 500, 2500);
}

/**
 * @brief Cria um objeto de Servo
 *
 * @param [in] position define a posição do servo
 * @return N/A.
 */
void ServoOS::setPosition(float position) {
  servo.write((int)position);
}

void ServoOS::setSpeed(double speed) {
  servo.write((int)speed);
}
