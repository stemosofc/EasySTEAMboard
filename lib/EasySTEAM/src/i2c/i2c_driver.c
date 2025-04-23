#include "i2c_driver.h"


uint32_t timeout = 200 / portTICK_PERIOD_MS;

const i2c_master_bus_config_t i2c_mst_config = {
    .i2c_port = -1,
    .sda_io_num = GPIO_NUM_21,
    .scl_io_num = GPIO_NUM_22,
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .glitch_ignore_cnt = 7,
    .intr_priority = 0,
    .flags.enable_internal_pullup = 1,
};

i2c_master_bus_handle_t i2c_bus_handle = NULL;

esp_err_t initialize_i2c_bus()
{
    if(i2c_bus_handle == NULL)
    {
        return i2c_new_master_bus(&i2c_mst_config, &i2c_bus_handle);
    }
    return ESP_OK;  
}

esp_err_t initialize_i2c_device(const i2c_device_config_t *dev_config, i2c_master_dev_handle_t *ret_handle)
{
    return i2c_master_bus_add_device(i2c_bus_handle, dev_config, ret_handle);
}

esp_err_t i2c_device_is_connected(uint16_t address)
{
    return i2c_master_probe(i2c_bus_handle, address, timeout);
}

esp_err_t i2c_write_data(i2c_master_dev_handle_t * i2c_dev, const uint8_t *write_buffer, size_t write_size)
{
    return i2c_master_transmit(*i2c_dev, write_buffer, write_size, timeout);
}

esp_err_t i2c_read_data(i2c_master_dev_handle_t * i2c_dev, const uint8_t *write_buffer, size_t write_size, uint8_t *read_buffer, size_t read_size)
{
    return i2c_master_transmit_receive(*i2c_dev, write_buffer, write_size, read_buffer, read_size, timeout);
}