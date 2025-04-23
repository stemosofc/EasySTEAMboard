#include "Servo.hpp"
#include "servo_low_level/servo-low-level.hpp"

ServoLL servoLowLevel;

EasyServo::EasyServo(Config_Servo::Port entrada)
{
    switch(entrada)
    {
        case Config_Servo::Port::PORTA_1:
            channel = 8;
            break;
        case Config_Servo::Port::PORTA_2:
            channel = 9;
            break;
        case Config_Servo::Port::PORTA_3: 
            channel = 10;
            break;
    }


    servoLowLevel.attach(entrada, channel);
}

void EasyServo::setPosition(int angleInDegrees)
{
    if(DS_ENABLE) 
        servoLowLevel.writeAngleDegrees(angleInDegrees);
}

int EasyServo::getPosition()
{
    return servoLowLevel.readAngleDegrees();
}
