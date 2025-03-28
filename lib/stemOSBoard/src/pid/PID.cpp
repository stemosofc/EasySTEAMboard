#include "PID.h"

PID::PID(double p, double i, double d) {
    this->p = p;
    this->i = i;
    this->d = d;
}


bool PID::atSetpoint() {
    return abs(positionError) < positionTolerance && abs(velocityError) < velocityTolerance;
}


void PID::setIZone(double iZone) {
    this->iZone = iZone;
}

void PID::isContinuousInputEnabled(double minimumInput, double maximumInput) {
    this->maximumInput = maximumInput;
}

void PID::setIntegratorRange(double minimumIntegral, double maximumIntegral) {
    minimumI = minimumIntegral;
    maximumI = maximumIntegral;
}


// Define a tolerância de saída do PID 
void PID::setTolerance(double positionTolerance, double velocityTolerance) {
    this->positionTolerance = positionTolerance;
    this->velocityTolerance = velocityTolerance;
}


// Calcula o valor de saída do PID (A saída NÃO é LIMITADA)
double PID::calculate(double measurement, double setpoint) {
    this->measurement = measurement;
    this->setpoint = setpoint;
    
    prevError = positionError;

    double time = (millis() / mToSeconds) - prevTime;

    if(continuous) {
        double errorBound = (maximumInput - minimumInput) / 2.0;
        positionError = inputModulus(setpoint - measurement, -errorBound, errorBound);
    } else {
        positionError = setpoint - measurement;
    }

    velocityError = (positionError - prevError) / time;

    if(abs(positionError ) > iZone) {
        totalError = 0;
    } else if(i != 0) {
        totalError = constrain(totalError + positionError * time, minimumI / i, maximumI / i);
    }
    

    prevTime = time;
    return (p * positionError) + (i * totalError) + (d * velocityError);
}

double PID::inputModulus(double input, double minimum, double maximum) {
    double modulus = maximumInput - minimumInput;

    // Wrap input if it's above the maximum input
    int numMax = (int) ((input - minimumInput) / modulus);
    input -= numMax * modulus;

    // Wrap input if it's below the minimum input
    int numMin = (int) ((input - maximumInput) / modulus);
    input -= numMin * modulus;

    return input;
}