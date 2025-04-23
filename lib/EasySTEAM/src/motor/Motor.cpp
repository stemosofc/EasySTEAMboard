#include "Motor.hpp"

/**
 * @brief Cria um objeto de Motor
 *
 * @param int entrada a porta na qual o motor esta conectado
 * @param int reverse define se o motor deve ser invertido ou não
 * @return N/A.
 */
Motor::Motor(int entrada, bool reverse) {
  pinos(entrada);

  if (!reverse) {
    ledcAttachChannel(pinPWMA, FREQUENCY, RESOLUTION, channelA);

    ledcAttachChannel(pinPWMB, FREQUENCY, RESOLUTION, channelB);
  } else {
    ledcAttachChannel(pinPWMA, FREQUENCY, RESOLUTION, channelB);

    ledcAttachChannel(pinPWMB, FREQUENCY, RESOLUTION, channelA);
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
      pinPWMA = GPIO_NUM_4;  
      pinPWMB = GPIO_NUM_13; 
      channelA = LEDC_CHANNEL_0;
      channelB = LEDC_CHANNEL_1;
      break;
    case Motor::PORTA_2: 
      pinPWMA = GPIO_NUM_18;
      pinPWMB = GPIO_NUM_19;
      channelA = LEDC_CHANNEL_2;
      channelB = LEDC_CHANNEL_3;
      break;
    case Motor::PORTA_3:
      pinPWMA = GPIO_NUM_23;
      pinPWMB = GPIO_NUM_25;
      channelA = LEDC_CHANNEL_4; 
      channelB = LEDC_CHANNEL_5;
      break;
    case Motor::PORTA_4:
      pinPWMA = GPIO_NUM_32; 
      pinPWMB = GPIO_NUM_33; 
      channelA = LEDC_CHANNEL_6;
      channelB = LEDC_CHANNEL_7;
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
  if(DS_ENABLE) {
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