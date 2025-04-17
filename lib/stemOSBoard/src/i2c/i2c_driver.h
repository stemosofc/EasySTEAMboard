#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include "master.h"
#include "driver/i2c_master.h"

esp_err_t initialize_i2c_bus();
esp_err_t initialize_i2c_device(const i2c_device_config_t *dev_config, i2c_master_dev_handle_t *ret_handle);
esp_err_t i2c_device_is_connected(uint16_t address);

esp_err_t i2c_write_data(i2c_master_dev_handle_t * i2c_dev, const uint8_t *write_buffer, size_t write_size);
esp_err_t i2c_read_data(i2c_master_dev_handle_t * i2c_dev, const uint8_t *write_buffer, size_t write_size, uint8_t *read_buffer, size_t read_size);


#endif