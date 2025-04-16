#include "driver/i2c.h"

#include "icm20948.h"
#include "icm20948_i2c.h"

uint32_t timeout = 5000 / portTICK_PERIOD_MS;

i2c_master_bus_handle_t i2c_bus_handle = NULL;

i2c_master_bus_config_t i2c_mst_config = {
    .i2c_port = -1,
    .sda_io_num = GPIO_NUM_21,
    .scl_io_num = GPIO_NUM_22,
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .glitch_ignore_cnt = 7,
    .intr_priority = 0
};

i2c_master_dev_handle_t *dev_handle = 0;

void i2c_initialize(const i2c_device_config_t *dev_config, i2c_master_dev_handle_t *ret_handle)
{
    if(i2c_bus_handle == NULL)
    {
        esp_err_t bus_result = i2c_new_master_bus(&i2c_mst_config, &i2c_bus_handle);
        log_i("Init I2C bus with code: %s", esp_err_to_name(bus_result));
    }

    esp_err_t device_result = i2c_master_bus_add_device(i2c_bus_handle, dev_config, ret_handle);
    dev_handle = ret_handle;
    log_i("Add device to I2C bus with code %s", esp_err_to_name(device_result));
}

icm20948_status_e icm20948_internal_write_i2c(uint8_t reg, uint8_t *data, uint32_t len, void *user)
{
	icm20948_status_e status = ICM_20948_STAT_OK;
	icm0948_config_i2c_t *args = (icm0948_config_i2c_t*)user;

    uint8_t data_write[(len+1)];
    data_write[0] = reg;
    for(int i=1; i<(len+1); i++)
        data_write[i] = data[i-1];

    if(i2c_master_transmit(*dev_handle, data_write, (len+1), timeout) != ESP_OK)
	{
		status = ICM_20948_STAT_ERR;
	}
    return status;
}

icm20948_status_e icm20948_internal_read_i2c(uint8_t reg, uint8_t *buff, uint32_t len, void *user)
{
	icm20948_status_e status = ICM_20948_STAT_OK;
	icm0948_config_i2c_t *args = (icm0948_config_i2c_t*)user;
    
	if(i2c_master_transmit_receive(*dev_handle, &reg, 1, buff, len, timeout) != ESP_OK)
	{
		status = ICM_20948_STAT_ERR;
	}
    return status;
}

/* default serif */
icm20948_serif_t default_serif = {
    icm20948_internal_write_i2c,
    icm20948_internal_read_i2c,
    NULL,
};

void icm20948_init_i2c(icm20948_device_t *icm_device, icm0948_config_i2c_t *args)
{
	icm20948_init_struct(icm_device);
	default_serif.user = (void *)args;
    icm20948_link_serif(icm_device, &default_serif);

#ifdef CONFIG_ICM_20948_USE_DMP
  icm_device->_dmp_firmware_available = true; // Initialize _dmp_firmware_available
#else
  icm_device->_dmp_firmware_available = false; // Initialize _dmp_firmware_available
#endif

    icm_device->_firmware_loaded = false; // Initialize _firmware_loaded
    icm_device->_last_bank = 255;         // Initialize _last_bank. Make it invalid. It will be set by the first call of icm20948_set_bank.
    icm_device->_last_mems_bank = 255;    // Initialize _last_mems_bank. Make it invalid. It will be set by the first call of inv_icm20948_write_mems.
    icm_device->_gyroSF = 0;              // Use this to record the GyroSF, calculated by inv_icm20948_set_gyro_sf
    icm_device->_gyroSFpll = 0;
    icm_device->_enabled_Android_0 = 0;      // Keep track of which Android sensors are enabled: 0-31
    icm_device->_enabled_Android_1 = 0;      // Keep track of which Android sensors are enabled: 32-
    icm_device->_enabled_Android_intr_0 = 0; // Keep track of which Android sensor interrupts are enabled: 0-31
    icm_device->_enabled_Android_intr_1 = 0; // Keep track of which Android sensor interrupts are enabled: 32-

}
