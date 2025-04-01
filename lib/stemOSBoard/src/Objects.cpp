#include "Objects.h"

Motor motor1(Motor::PORTA_1, Motor::FORWARD);
Motor motor2(Motor::PORTA_2, Motor::FORWARD);
Motor motor3(Motor::PORTA_3, Motor::FORWARD);
Motor motor4(Motor::PORTA_4, Motor::FORWARD);

EasyServo servo1(Servo::ServoPorts::PORTA_1);
EasyServo servo2(Servo::ServoPorts::PORTA_1);
EasyServo servo3(Servo::ServoPorts::PORTA_1);

Digital di1(IOPorts::PORTA_1);
Digital di2(IOPorts::PORTA_2);
Digital di3(IOPorts::PORTA_3);
Digital di4(IOPorts::PORTA_4);
Digital di5(IOPorts::PORTA_5);

IMU imu;

//SensorColor sensorColor;


void Control::disableMotors() {

}

void Control::disableServos() {

}

void Control::stopAll() {

}

void Control::enableAll() {

}
