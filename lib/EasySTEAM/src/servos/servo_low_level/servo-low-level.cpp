#include "servo-low-level.hpp"

static const char * TAG_SERVO = "Servo";

void ServoLL::attach(uint8_t pin, uint32_t min, uint32_t max, uint8_t channel)
{
    this->pin = pin;

    // min/max checks 
    if (min < DEFAULT_MIN_PULSE)          // ensure pulse width is valid
        min = DEFAULT_MIN_PULSE;
    if (max > DEFAULT_MAX_PULSE)
        max = DEFAULT_MAX_PULSE;

    // Set up this channel
    // if you want anything other than default timer width, you must call setTimerWidth() before attach

    if(!ledcAttach(pin, DEFAULT_FREQUENCY, DEFAULT_RESOLUTION_BITS))
        log_e("Failed Servo Attached on pin(%d), freq(%d), resl(%d)", pin, DEFAULT_FREQUENCY, DEFAULT_RESOLUTION_BITS);
}

void ServoLL::attach(uint8_t pin, uint8_t channel)
{
    attach(pin, DEFAULT_MIN_PULSE, DEFAULT_MAX_PULSE, channel);
}

void ServoLL::writeAngleDegrees(uint16_t angleInDegrees)
{
    writeMicroseconds(angleToUs(angleInDegrees));
}

void ServoLL::writeMicroseconds(uint32_t microseconds)
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

uint32_t ServoLL::readMicroseconds()
{
    return ticksToUs(currentTicks);
}

uint32_t ServoLL::readTicks()
{
    return currentTicks;
}

uint32_t ServoLL::usToTicks(uint32_t usec)
{
    return (int)((double)usec / ((double)DEFAULT_REFRESH_USEC / (double)this->DEFAULT_TIMER_WIDTH_TICKS)*(((double)DEFAULT_FREQUENCY)/50.0));
}

uint32_t ServoLL::ticksToUs(uint32_t ticks)
{
    return (int)((double)ticks * ((double)DEFAULT_REFRESH_USEC / (double)this->DEFAULT_TIMER_WIDTH_TICKS)/(((double)DEFAULT_FREQUENCY)/50.0));
}

uint32_t ServoLL::angleToUs(uint16_t angleInDegrees)
{
    return map(angleInDegrees, DEFAULT_ANGLE_MIN_DEGREES, DEFAULT_ANGLE_MAX_DEGREES, DEFAULT_MIN_PULSE, DEFAULT_MAX_PULSE);
}