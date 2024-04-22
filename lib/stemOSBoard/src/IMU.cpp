#include "IMU.h"

IMU::IMU() {
  if (!icm.begin_I2C(0x68)) {
    if (Serial) {
      Serial.println("IMU chip not found");
    }
  }
}

void IMU::update() {
  icm.getEvent(&accel, &gyro, &temp, &mag);
  delayMicroseconds(timeDelay);
}


float IMU::getWAccelX() {
  return gyro.gyro.x;
}

float IMU::getWAccelZ() {
  return gyro.gyro.z;
}

float IMU::getWAccelY() {
  return gyro.gyro.z;
}

float IMU::getAccelX() {
  return accel.acceleration.x;
}

float IMU::getAccelY() {
  return accel.acceleration.y;
}

float IMU::getAccelZ() {
  return accel.acceleration.z;
}

float IMU::getX() {
  return mag.magnetic.x;
}

float IMU::getZ() {
  return mag.magnetic.z;
}

float IMU::getY() {
  return mag.magnetic.y;
}

float IMU::getTemperature() {
  return temp.temperature;
}