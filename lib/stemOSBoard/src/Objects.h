#pragma once

#include "Arduino.h"
#include "Motor.h"
#include "Digital.h"
#include "servos/ServoOS.h"
#include "Analog.h"
//#include "IMU.h"
#include "PID.h"
#include "color_sensor/SensorColor.h"

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

//extern IMU imu;

extern SensorColor sensorColor;

class Control {
    private:
        friend class stemWiFi;
        static void stopAll();
        static void enableAll();
        static void disableMotors();
        static void disableServos();
};
