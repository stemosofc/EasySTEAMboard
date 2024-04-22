#ifndef Servo_h
#define Servo_h
#include "Arduino.h"

enum PortaServo {
  PORTA_1_SERVO = 2,
  PORTA_2_SERVO = 26,
  PORTA_3_SERVO = 27,
};

  class Servo {
    public:
      Servo(PortaServo entrada);
      void setPosition(float position);
    private:
      static const int FREQUENCY = 9000;
      static const int RESOLUTION = 8;
      int channel;
      int signalPin;
  };
#endif
