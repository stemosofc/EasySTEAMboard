#include "Servo.h"

EasyServo::EasyServo(Servo::PortaServo entrada)
{
    switch(entrada)
    {
        case Servo::PortaServo::PORTA_1:
            channel = 8;
            break;
        case Servo::PortaServo::PORTA_2:
            channel = 9;
            break;
        case Servo::PortaServo::PORTA_3: 
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
