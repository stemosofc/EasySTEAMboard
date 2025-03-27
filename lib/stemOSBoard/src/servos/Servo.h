#ifndef SERVOOS_H
#define SERVOOS_H

#include "Arduino.h"
#include "servo_low_level/servo-low-level.h"

namespace Servo {
    enum PortaServo {
        PORTA_1 = 2,
        PORTA_2 = 26,
        PORTA_3 = 27,
    };
}

class EasyServo {
    public:
        EasyServo(Servo::PortaServo entrada);
        void setPosition(int angleInDegrees);
        int getPosition();
    private:
        ServoLL servoLowLevel;
        int channel;
        int pinNumber;
};

#endif
