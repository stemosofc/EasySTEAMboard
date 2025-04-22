#ifndef Encoder_h
#define Encoder_h

#include "master.h"

namespace Config_Encoder
{
    enum EncoderPorts
    {
        PORTA_1 = 1,
        PORTA_2 = 2,
    };
}

class Encoder : private EncoderLL
{
    public:
        Encoder(Config_Encoder::EncoderPorts port);
        float getPosition();
        void reset();
        void setPositionFactor(float factor);
    private:
        gpio_num_t pinA;
        gpio_num_t pinB;
        float factorOfConversion = 1;
};

#endif