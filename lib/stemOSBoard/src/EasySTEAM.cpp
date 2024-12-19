#include <EasySTEAM.h>

void EasySTEAM::stopAll() {
    stopMotors();
    stopServos();
    stopSensors();
}

void EasySTEAM::stopMotors() {
    motor1.setPower(0);
    motor2.setPower(0);
    motor3.setPower(0);
    motor4.setPower(0);
}

void EasySTEAM::stopServos() {
    // caso servo esteja em continous mode é necessário para0-lós
}

void EasySTEAM::stopSensors() {

}