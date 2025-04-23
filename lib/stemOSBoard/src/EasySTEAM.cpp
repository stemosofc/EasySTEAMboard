#include "EasySTEAM.h"

Encoder encoder1(Config_Encoder::EncoderPorts::PORTA_1);
Encoder encoder2(Config_Encoder::EncoderPorts::PORTA_2);

EasyServo servo1(Config_Servo::Port::PORTA_1);
EasyServo servo2(Config_Servo::Port::PORTA_2);
EasyServo servo3(Config_Servo::Port::PORTA_3);

Motor motor1(Motor::PORTA_1);
Motor motor2(Motor::PORTA_2);
Motor motor3(Motor::PORTA_3);
Motor motor4(Motor::PORTA_4);

Digital di1(Config_IO::PORTA_1);
Digital di2(Config_IO::PORTA_2);
Digital di3(Config_IO::PORTA_3);
Digital di4(Config_IO::PORTA_4);
Digital di5(Config_IO::PORTA_5);

IMU imu;
ColorSensor colorSensor;

stemWiFi easySTEAM;

Gamepad gamepad;