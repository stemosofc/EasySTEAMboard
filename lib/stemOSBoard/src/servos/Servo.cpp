#include "Servo.h"

EasyServo::EasyServo(Servo::ServoPorts entrada)
{
    switch(entrada)
    {
        case Servo::ServoPorts::PORTA_1:
            channel = 8;
            break;
        case Servo::ServoPorts::PORTA_2:
            channel = 9;
            break;
        case Servo::ServoPorts::PORTA_3: 
            channel = 10;
            break;
    }


    servoLowLevel.attach(entrada, channel);
}

void EasyServo::setPosition(int angleInDegrees)
{
    servoLowLevel.writeAngleDegrees(angleInDegrees);
}

int EasyServo::getPosition()
{
    return servoLowLevel.readAngleDegrees();
}
