#pragma once

#include "Arduino.h"

#include "motor/Motor.h"
#include "digital/Digital.h"
#include "servos/Servo.h"
#include "analog/Analog.h"
#include "imu/IMU.h"
#include "pid/PID.h"

extern Motor motor1;
extern Motor motor2;
extern Motor motor3;
extern Motor motor4;

extern EasyServo servo1;
extern EasyServo servo2;
extern EasyServo servo3;

extern Digital di1;
extern Digital di2;
extern Digital di3;
extern Digital di4;
extern Digital di5;

extern IMU imu;

extern SensorColor sensorColor;

class Control {
    private:
        friend class stemWiFi;
        static void stopAll();
        static void enableAll();
        static void disableMotors();
        static void disableServos();
};
