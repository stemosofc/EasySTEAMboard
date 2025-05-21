#ifndef _EASYSTEAM_H
#define _EASYSTEAM_H

#include "digital/Digital.hpp"
#include "motor/Motor.hpp"
#include "encoder/Encoder.hpp"
#include "servos/Servo.hpp"
#include "i2c/imu/imu.hpp"
#include "i2c/color_sensor/ColorSensor.hpp"
#include "i2c/pinpoint/pinpoint.hpp"
#include "gamepad/Gamepad.h"

extern Encoder encoder1;
extern Encoder encoder2;

extern Digital di1;
extern Digital di2;
extern Digital di3;
extern Digital di4;
extern Digital di5;

extern IMU imu;
extern ColorSensor colorSensor;
extern PinPoint pinPoint; 

extern Motor motor1;
extern Motor motor2;
extern Motor motor3;
extern Motor motor4;

extern EasyServo servo1;
extern EasyServo servo2;
extern EasyServo servo3;

extern Gamepad gamepad;

class EasySTEAM {
    public:
        void start();
    private:
        inline void waitForEnable();
};

extern EasySTEAM easySTEAM;

#endif

