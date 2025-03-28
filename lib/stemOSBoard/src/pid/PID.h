#ifndef PID_H
#define PID_H

#include "Arduino.h"

class PID {
    public:
        PID(double p, double i, double d);
        double calculate(double setPoint, double measurement);
        void setSetpoint(double setPoint);
        void setTolerance(double positionTolerance, double velocity=infinity());
        void setIntegratorRange(double minimumIntegral, double maximumIntegral);
        void isContinuousInputEnabled(double minimumInput, double maximumInput);
        bool atSetpoint();
        void setIZone(double iZone);
    private:
        double p;
        double i;
        double d;
        double setpoint;
        double positionError;
        double positionTolerance;
        double velocityTolerance;
        double prevError;
        double measurement;
        double totalError;
        bool continuous = false;
        double maximumI;
        double minimumI;
        double iZone;
        double maximumInput;
        double minimumInput;
        double prevTime;
        double velocityError;
        static const int mToSeconds = 1000;
        double inputModulus(double input, double minimumInput, double maximumInput);
};

#endif 