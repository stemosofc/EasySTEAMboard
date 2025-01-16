#ifndef SERVOOS_H
#define SERVOOS_H
#include "Servo.h"

enum PortaServo {
  PORTA_1_SERVO = 2,
  PORTA_2_SERVO = 26,
  PORTA_3_SERVO = 27,
};

class ServoOS {
    public:
      ServoOS(PortaServo entrada);
      void setPosition(float position);
      void setSpeed(double speed);
    private:
      friend class EasySTEAM;
      static const int FREQUENCY = 9000;
      static const int RESOLUTION = 8;
      static const int ANGLE_MAX = 270;
      static const int ANGLE_MIN = 0;
      static const int MIN_PULSE = 500;
      static const int MAX_PULSE = 2500; 
      int channel;
      int signalPin;
      Servo servo;
      static bool connect;
      static void disable();
      static void enable();
};
#endif
