#ifndef SensorColor_h
#define SensorColor_h

#include "APDS9151.h"
#include "esp32-hal-log.h"

class SensorColor
{
    public:
        SensorColor(void);
        int getGreen(void);
        int getRed(void);
        int getBlue(void);
        int getPS(void);
        int getIR(void);
        void start(void);
};


#endif
