#ifndef SERVOOS_H
#define SERVOOS_H

#include "master.h"
#include "servo_low_level/servo-low-level.hpp"
namespace Config_Servo {
    enum Port {
        PORTA_1 = GPIO_NUM_2,
        PORTA_2 = GPIO_NUM_26,
        PORTA_3 = GPIO_NUM_27,
    };
}

class EasyServo {
    public:
        explicit EasyServo(Config_Servo::Port entrada);
        void setPosition(int angleInDegrees);
        int getPosition();
    private:
        int channel;
        ServoLL servoLowLevel;
};

#endif
