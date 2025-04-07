#include "servo-low-level.h"

void ServoLL::attach(int pin, int min, int max, int channel)
{
    this->pin = pin;

    log_d("Attempting to Attach servo on pin=%d min=%d max=%d", pin,min,max);

    // min/max checks 
    if (min < DEFAULT_MIN_PULSE)          // ensure pulse width is valid
        min = DEFAULT_MIN_PULSE;
    if (max > DEFAULT_MAX_PULSE)
        max = DEFAULT_MAX_PULSE;

    // Set up this channel
    // if you want anything other than default timer width, you must call setTimerWidth() before attach

    if(ledcAttachChannel(pin, DEFAULT_FREQUENCY, DEFAULT_RESOLUTION_BITS, channel))
        log_i("Successful Servo Attached on pin(%d), freq(%d), resl(%d) and channel(%d)", pin, DEFAULT_FREQUENCY, DEFAULT_RESOLUTION_BITS, channel);
    else
        log_e("Servo don't Attached on pin(%d), freq(%d), resl(%d) and channel(%d)", pin, DEFAULT_FREQUENCY, DEFAULT_RESOLUTION_BITS, channel);
}

void ServoLL::attach(int pin, int channel)
{
    attach(pin, DEFAULT_MIN_PULSE, DEFAULT_MAX_PULSE, channel);
}

void ServoLL::writeAngleDegrees(int angleInDegrees)
{
    writeMicroseconds(angleToUs(angleInDegrees));
}

void ServoLL::writeMicroseconds(int microseconds)
{
    writeTicks(usToTicks(microseconds));  // convert to ticks
}

void ServoLL::writeTicks(uint32_t ticks)
{
    currentTicks = ticks;
    ledcWrite(pin, ticks);
}

int ServoLL::readAngleDegrees()
{
    return (map(readMicroseconds(), DEFAULT_MIN_PULSE, DEFAULT_MAX_PULSE, DEFAULT_ANGLE_MIN_DEGREES, DEFAULT_ANGLE_MAX_DEGREES));
}

int ServoLL::readMicroseconds()
{
    return ticksToUs(currentTicks);
}

int ServoLL::readTicks()
{
    return currentTicks;
}

int ServoLL::usToTicks(int usec)
{
    return (int)((double)usec / ((double)DEFAULT_REFRESH_USEC / (double)this->DEFAULT_TIMER_WIDTH_TICKS)*(((double)DEFAULT_FREQUENCY)/50.0));
}

int ServoLL::ticksToUs(int ticks)
{
    return (int)((double)ticks * ((double)DEFAULT_REFRESH_USEC / (double)this->DEFAULT_TIMER_WIDTH_TICKS)/(((double)DEFAULT_FREQUENCY)/50.0));
}

int ServoLL::angleToUs(int angleInDegrees)
{
    return map(angleInDegrees, DEFAULT_ANGLE_MIN_DEGREES, DEFAULT_ANGLE_MAX_DEGREES, DEFAULT_MIN_PULSE, DEFAULT_MAX_PULSE);
}