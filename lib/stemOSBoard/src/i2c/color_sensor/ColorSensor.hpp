#ifndef SensorColor_h
#define SensorColor_h

// class for use of sensor color

class ColorSensor
{
    public:
        int getGreen(void);
        int getRed(void);
        int getBlue(void);
        int getPS(void);
        int getIR(void);
        void start(void);
};


#endif
