#include "Motor.h"

/**
 * @brief Cria um objeto de Motor
 *
 * @param int entrada a porta na qual o motor esta conectado
 * @param int reverse define se o motor deve ser invertido ou não
 * @return N/A.
 */
Motor::Motor(int entrada, bool reverse) {
  pinos(entrada);

  if (reverse) {
    ledcSetup(channelA, Motor::FREQUENCY, Motor::RESOLUTION);
    ledcAttachPin(pinPWMA, channelA);

    ledcSetup(channelB, Motor::FREQUENCY, Motor::RESOLUTION);
    ledcAttachPin(pinPWMB, channelB);
  } else {
    ledcSetup(channelA, Motor::FREQUENCY, Motor::RESOLUTION);
    ledcAttachPin(pinPWMA, channelB);

    ledcSetup(channelB, Motor::FREQUENCY, Motor::RESOLUTION);
    ledcAttachPin(pinPWMB, channelA);
  }

  if(Motor::PORTA_1 ^ Motor::PORTA_2) {
   // Encoder encoder(entrada);
    Encoder encoderESP(entrada);
  //  this->encoder = encoder;
    this->encoder = encoderESP;
  }

  ledcWrite(channelA, 0);
  ledcWrite(channelB, 0);
}


/**
 * @brief Define as entradas digitais da Arara baseado na porta do motor
 *
 * @param [in] Porta na qual o motor esta conectado
 * @return N/A.
 */
void Motor::pinos(int entrada) {
  switch (entrada) {
    case Motor::PORTA_1:
      pinPWMA = 4; 
      pinPWMB = 13;
      channelA = 0;
      channelB = 1;
      break;
    case Motor::PORTA_2:
      pinPWMA = 18;
      pinPWMB = 19;
      channelA = 2;
      channelB = 3;
      break;
    case Motor::PORTA_3:
      pinPWMA = 23;
      pinPWMB = 25;
      channelA = 4;
      channelB = 5;
      break;
    case Motor::PORTA_4:
      pinPWMA = 32;
      pinPWMB = 33;
      channelA = 6;
      channelB = 7;
      break;
  }
}


/**
 * @brief Define a velocidade do motor
 *
 * @param [in] power - range de [-1.0, 1.0]
 * @return N/A.
 */
void Motor::setPower(double power) {
  power = max(-1.0, min(1.0, power));
  int output_res = abs(power) * MAX_OUTPUT;
  if (power < 0) {
    ledcWrite(channelA, 0);
    ledcWrite(channelB, output_res);
  } else if(power > 0){
    ledcWrite(channelB, 0);
    ledcWrite(channelA, output_res);
  } else {
    ledcWrite(channelA, 0);
    ledcWrite(channelB, 0);
  }
}
