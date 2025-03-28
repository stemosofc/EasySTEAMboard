#include "Encoder.h"

Encoder::Encoder(Config_Encoder::EncoderPorts encoderPort)
{
    switch(encoderPort)
    {
        case Config_Encoder::EncoderPorts::PORTA_1_ENCODER:
            pinA = GPIO_NUM_5;
            pinB = GPIO_NUM_14;
            break;
        case Config_Encoder::EncoderPorts::PORTA_2_ENCODER:
            pinA = GPIO_NUM_15;
            pinB = GPIO_NUM_16;
            break;
    }

    encoderLowLevel.initialize(pinA, pinB);
}

float Encoder::getPosition()
{
    return encoderLowLevel.getCount() * factorOfConversion;
}

void Encoder::setPositionFactor(float factor)
{
    factorOfConversion = factor;
}

void Encoder::reset()
{
    encoderLowLevel.reset();
}

