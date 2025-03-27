#ifndef servo_low_level_h
#define servo_low_level_h

#include "esp32-hal-log.h"
#include "Arduino.h"

class ServoLL
{
    public:
        void attach(int pin, int minPulse, int maxPulse, int channel);
        void attach(int pin, int channel);
        void writeAngleDegrees(int angleInDegrees); 
        int readAngleDegrees();

    private:
        static const int DEFAULT_ANGLE_MAX_DEGREES = 270;
        static const int DEFAULT_ANGLE_MIN_DEGREES = 0;
        static const int DEFAULT_MIN_PULSE = 500;
        static const int DEFAULT_MAX_PULSE = 2500; 
        static const int DEFAULT_FREQUENCY = 50; 
        static const int DEFAULT_RESOLUTION_BITS = 10;
        static const int DEFAULT_REFRESH_USEC = 20000;
        static const int DEFAULT_TIMER_WIDTH_TICKS = 1024;
        
        int maxAngle = 0;
        int minAngle = 0;
        int pin = -1;
        int currentTicks = 0;

        int usToTicks(int usec);
        int ticksToUs(int ticks);
        int angleToUs(int angleInDegrees);

        void writeMicroseconds(int microseconds);    
        void writeTicks(uint32_t ticks);   
        
        int readMicroseconds();
        int readTicks();
};


#endif