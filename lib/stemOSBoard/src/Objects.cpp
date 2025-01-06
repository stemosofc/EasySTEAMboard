#include "Objects.h"

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

void Control::disableMotors() {
    Motor::stop();
    motor1.setPower(0);
    motor2.setPower(0);
    motor3.setPower(0);
    motor4.setPower(0);
}

void Control::stopAll() {
    disableMotors();
}

void Control::enableAll() {
    Motor::enable();
}
