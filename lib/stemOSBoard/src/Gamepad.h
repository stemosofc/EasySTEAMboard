#ifndef Gamepad_h
#define Gamepad_h
#include <ArduinoJson.h>
#include "Arduino.h"

class Gamepad {
  public:
    void applyDeadband(double deadband = 0.01);
    double getLeftAxisY();
    double getLeftAxisX();
    double getRightAxisY();
    double getRightAxisX();
    bool getButtonA();
    bool getButtonB();
    bool getButtonX();
    bool getButtonY();
    bool getRightBumper();
    bool getLeftBumper();
    double getRightTrigger();
    double getLeftTrigger();
    static JsonDocument gamepad;
  private:
    double deadband = 0.01;
    double maxMagnitude = 1;
    double getValue(double value);
};

#endif