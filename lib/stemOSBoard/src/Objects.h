#pragma once

#include "Arduino.h"
#include "motor/Motor.h"
#include "digital/Digital.h"
#include "servos/ServoOS.h"
#include "analog/Analog.h"
#include "imu/IMU.h"
#include "pid/PID.h"

extern Motor motor1;
extern Motor motor2;
extern Motor motor3;
extern Motor motor4;

extern ServoOS servo1;
extern ServoOS servo2;
extern ServoOS servo3;

extern Digital di1;
extern Digital di2;
extern Digital di3;
extern Digital di4;
extern Digital di5;

extern IMU imu;

class Control {
    private:
        friend class stemWiFi;
        static void stopAll();
        static void enableAll();
        static void disableMotors();
        static void disableServos();
};
