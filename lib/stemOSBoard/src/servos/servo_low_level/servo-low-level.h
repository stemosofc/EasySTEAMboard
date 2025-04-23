#ifndef _SERVO_LOW_LEVEL_h_
#define _SERVO_LOW_LEVEL_h_

#include "master.h"

class ServoLL
{
    public:
        void attach(uint8_t pin, uint32_t minPulse, uint32_t maxPulse, uint8_t channel);
        void attach(uint8_t pin, uint8_t channel);
        void writeAngleDegrees(uint16_t angleInDegrees); 
        int readAngleDegrees();

    private:
        static const int DEFAULT_ANGLE_MAX_DEGREES = 270;
        static const int DEFAULT_ANGLE_MIN_DEGREES = 0;
        static const int DEFAULT_MIN_PULSE = 500;
        static const int DEFAULT_MAX_PULSE = 2500; 
        static const int DEFAULT_FREQUENCY = 50; 
        static const int DEFAULT_RESOLUTION_BITS = LEDC_TIMER_10_BIT;
        static const int DEFAULT_REFRESH_USEC = 20000;
        static const int DEFAULT_TIMER_WIDTH_TICKS = 1024;
        
        int maxAngle = 0;
        int minAngle = 0;
        int pin = -1;
        int currentTicks = 0;

        uint32_t usToTicks(uint32_t usec);
        uint32_t ticksToUs(uint32_t ticks);
        uint32_t angleToUs(uint16_t angleInDegrees);

        void writeMicroseconds(uint32_t microseconds);    
        void writeTicks(uint32_t ticks);   
        
        uint32_t readMicroseconds();
        uint32_t readTicks();
};


#endif