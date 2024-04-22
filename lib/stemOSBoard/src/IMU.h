#ifndef IMU_h
#define IMU_h

#include "Arduino.h"
#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20948.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_ipc.h>

class IMU {
public:
  IMU(void);
  char getAccelRange();
  int getGyroRange();
  float getAccelRate();
  char getMagDataRate();
  float getAcceleration();
  float getX();
  float getZ();
  float getY();
  float getAccelX();
  float getAccelY();
  float getAccelZ();
  float getTemperature();
  float getWAccelX();
  float getWAccelY();
  float getWAccelZ();
  void update();
private:
  Adafruit_ICM20948 icm;
  uint16_t timeDelay = 65535;
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t mag;
  sensors_event_t temp;
};

#endif