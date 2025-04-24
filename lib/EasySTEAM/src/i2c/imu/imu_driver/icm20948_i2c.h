#ifndef _ICM_20948_I2C_H_
#define _ICM_20948_I2C_H_

#include "i2c/i2c_driver.h"

static const char * TAG_IMU = "IMU";

typedef struct
{
	i2c_port_t i2c_port;
	uint8_t i2c_addr;
} icm0948_config_i2c_t;

void icm20948_init_i2c(icm20948_device_t *device, icm0948_config_i2c_t *config);
void i2c_initialize(const i2c_device_config_t *dev_config, i2c_master_dev_handle_t *ret_handle);
/* these functions are exposed in order to make a custom setup of a serif_t possible */
icm20948_status_e icm20948_internal_write_i2c(uint8_t reg, uint8_t *data, uint32_t len, void *user);
icm20948_status_e icm20948_internal_read_i2c(uint8_t reg, uint8_t *buff, uint32_t len, void *user);

#endif