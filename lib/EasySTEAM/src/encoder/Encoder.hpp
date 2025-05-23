#ifndef Encoder_h
#define Encoder_h

#include "master.h"
#include "encoder_low_level/encoder-low-level.hpp"

namespace Config_Encoder
{
    enum EncoderPorts
    {
        PORTA_1 = 1,
        PORTA_2 = 2,
    };
}

class Encoder
{
    public:
        Encoder(Config_Encoder::EncoderPorts port);
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