#include "Motor.h"

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
    EncoderESP encoderESP(entrada);
  //  this->encoder = encoder;
    this->encoderESP = encoderESP;
  }
}

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

void Motor::setPower(double power) {
  power = max(-1.0, min(1.0, power));
  double output_res = abs(power) * 1023;
  if (power < 0) {
    ledcWrite(channelB, output_res);
  } else {
    ledcWrite(channelA, output_res);
  }
}
