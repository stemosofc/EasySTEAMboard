#ifndef Encoder_h
#define Encoder_h

#include "encoder_low_level/encoder-low-level.h"

namespace Config_Encoder
{
    enum EncoderPorts
    {
        PORTA_1_ENCODER = 1,
        PORTA_2_ENCODER = 2,
    };
}

class Encoder : public EncoderLL
{
    public:
        Encoder(Config_Encoder::EncoderPorts encoderPort);
        float getPosition();
        void reset();
        void setPositionFactor(float factor);
    private:
        EncoderLL encoderLowLevel;
        gpio_num_t pinA;
        gpio_num_t pinB;
        float factorOfConversion = 1;
};

#endif