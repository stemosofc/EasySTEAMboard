#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include "master.h"
#include "driver/i2c_master.h"

esp_err_t initialize_i2c_bus();
esp_err_t initialize_i2c_device();
esp_err_t i2c_device_is_connected();

esp_err_t i2c_write_data();
esp_err_t i2c_read_data();


#endif