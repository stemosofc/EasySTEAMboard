#include "Motor.h"

bool Motor::connection = false;

/**
 * @brief Cria um objeto de Motor
 *
 * @param int entrada a porta na qual o motor esta conectado
 * @param int reverse define se o motor deve ser invertido ou não
 * @return N/A.
 */
Motor::Motor(int entrada, bool reverse) : encoder(entrada) {
  pinos(entrada);

  if (reverse) {
    ledcAttachChannel(pinPWMA, Motor::FREQUENCY, Motor::RESOLUTION, channelA);

    ledcAttachChannel(pinPWMB, Motor::FREQUENCY, Motor::RESOLUTION, channelB);
  } else {
    ledcAttachChannel(pinPWMA, Motor::FREQUENCY, Motor::RESOLUTION, channelB);

    ledcAttachChannel(pinPWMB, Motor::FREQUENCY, Motor::RESOLUTION, channelA);
  }

  ledcWriteChannel(channelA, 0);
  ledcWriteChannel(channelB, 0);
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
  if(connection) {
    power = max(-1.0, min(1.0, power));
    int output_res = abs(power) * MAX_OUTPUT;
    if (power < 0) {
      ledcWriteChannel(channelA, 0);
      ledcWriteChannel(channelB, output_res);
    } else if(power > 0) {
      ledcWriteChannel(channelB, 0);
      ledcWriteChannel(channelA, output_res);
    } else {
      ledcWriteChannel(channelA, 0);
      ledcWriteChannel(channelB, 0);
    }
  } else {
    ledcWriteChannel(channelA, 0);
    ledcWriteChannel(channelB, 0);
  }
}

void Motor::stop() {
  connection = false;
}

void Motor::enable() {
  connection = true;
}