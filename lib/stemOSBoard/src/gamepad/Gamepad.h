#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <ArduinoJson.h>
#include "Arduino.h"

class Gamepad {
  public:
    Gamepad(void);
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
    static bool status();
    static void reset();
    friend class stemWiFi;
};

#endif