#ifndef stemOSboard_h
#define stemOSboard_h
#include "Arduino.h"
#include "Motor.h"
#include "Gamepad.h"
#include "Digital.h"
#include "ServoOS.h"
#include "Analog.h"
#include "IMU.h"
#include "PID.h"
#include "stemWiFi.h"

Motor motor1(Motor::PORTA_1, Motor::FORWARD);
Motor motor2(Motor::PORTA_2, Motor::FORWARD);
Motor motor3(Motor::PORTA_3, Motor::FORWARD);
Motor motor4(Motor::PORTA_4, Motor::FORWARD);

ServoOS servo1(PORTA_1_SERVO);
ServoOS servo2(PORTA_2_SERVO);
ServoOS servo3(PORTA_3_SERVO);

Digital di1(PortasDigitais::PORTA_1);
Digital di2(PortasDigitais::PORTA_2);
Digital di3(PortasDigitais::PORTA_3);
Digital di4(PortasDigitais::PORTA_4);
Digital di5(PortasDigitais::PORTA_5);

IMU imu;

stemWiFi easySTEAM;

Gamepad gamepad;

#endif
