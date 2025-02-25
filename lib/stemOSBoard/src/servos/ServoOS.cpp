#include "ServoOS.h"

bool ServoOS::connect = false;
int initialized = 0;
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
  if(!initialized)
  {
    ESP32PWM::allocateTimer(3);
    initialized = 1;
  }

  servo.attach(entrada, MIN_PULSE, MAX_PULSE);
}

/**
 * @brief Define a posição do servo
 *
 * @param [in] position define a posição do servo
 * @return N/A.
 */
void ServoOS::setPosition(float position) {
  if(!connect) return;
  servo.write((int)position);
}

/**
 * @brief Define a velocidade do servo no modo contínuo
 *
 * @param [in] speed define a velocidade do servo
 * @return N/A.
 */
void ServoOS::setSpeed(double speed) {
  speed = max(0.0, min(1.0, speed));
  int vel = speed * ANGLE_MAX;
  servo.write(vel);
}

void ServoOS::disable() {
  connect = false;
}

void ServoOS::enable() {
  connect = true;
}
