#include "driver_pinpoint.h"
#include "i2c/i2c_driver.h"

#define ACK_ENABLED 0
#define I2C_SPEED 100000
#define I2C_ADDRESS_LENGHT I2C_ADDR_BIT_LEN_7

i2c_device_config_t pinpoint_i2c_configure = 
{
    .dev_addr_length = I2C_ADDRESS_LENGHT, 
    .device_address = PINPOINT_I2C_ADDRESS,
    .scl_speed_hz = I2C_SPEED,
    .flags = {.disable_ack_check = ACK_ENABLED}
};


i2c_master_dev_handle_t pinpoint_dev_handle = NULL;

void init_pinpoint_i2c(void)
{
    esp_err_t result = initialize_i2c_bus();
    if(result) log_e("Error starting I2C from PinPoint, with code: %s", esp_err_to_name(result));
    result = initialize_i2c_device(&pinpoint_i2c_configure, &pinpoint_dev_handle);
    if(result) log_e("Error adding Pinpoint to I2C bus with code: %s", esp_err_to_name(result));
}

bool pinpoint_is_connected()
{
    return i2c_device_is_connected(PINPOINT_I2C_ADDRESS) == ESP_OK;
}

uint32_t get_device_id(void)
{
    uint8_t id[4] = {0};
    read_register(DEVICE_ID_ADDR, sizeof(id), id);
    return to_32_bit(id);
}

uint32_t get_device_version(void)
{
    uint8_t version[4] = {0};
    read_register(DEVICE_VERSION_ADDR, sizeof(version), version);
    return to_32_bit(version);
}

void get_device_status(device_status_t * device_status)
{
    read_register(DEVICE_STATUS_ADDR, sizeof(*device_status), device_status->device_status_u8);
}


void set_device_control(device_control_t * device_control)
{
    write_register(DEVICE_CONTROL_ADDR, device_control->device_control_u8);
}

uint32_t get_loop_time_us(void)
{
    uint8_t loop_time[4] = {0};
    read_register(LOOP_TIME_ADDR, sizeof(loop_time), loop_time);
    return to_32_bit(loop_time);
}

double get_frequency(void)
{
    return (pow(10, 6) / ((double)get_loop_time_us()));
}

uint32_t get_raw_x_encoder(void)
{
    uint8_t raw_x_encoder_value[4] = {0};
    read_register(X_ENCODER_VALUE_ADDR, sizeof(raw_x_encoder_value), raw_x_encoder_value);
    return to_32_bit(raw_x_encoder_value);
}

uint32_t get_raw_y_encoder(void)
{
    uint8_t raw_y_encoder_value[4] = {0};
    read_register(Y_ENCODER_VALUE_ADDR, sizeof(raw_y_encoder_value), raw_y_encoder_value);
    return to_32_bit(raw_y_encoder_value);
}

void get_x_position(x_position_t * x_pose)
{
    read_register(X_POSITION_ADDR, sizeof(*x_pose), x_pose->u8_x_position);
}

void get_y_position(y_position_t * y_pose)
{
    read_register(Y_POSITION_ADDR, sizeof(*y_pose), y_pose->u8_y_position);
}

void get_heading(h_orientation_t * heading)
{
    read_register(H_ORIENTATION_ADDR, sizeof(*heading), heading->u8_heading);
}

void set_x_position(x_position_t * x_position)
{
    write_register(X_POSITION_ADDR, x_position->u8_x_position);
}

void set_y_position(y_position_t * y_position)
{
    write_register(Y_POSITION_ADDR, y_position->u8_y_position);
}

void set_heading(h_orientation_t * orientation)
{
    write_register(H_ORIENTATION_ADDR, orientation->u8_heading);
}

void get_x_velocity(x_velocity_t * x_velocity)
{
    read_register(X_VELOCITY_ADDR, sizeof(*x_velocity), x_velocity->u8_x_velocity);
}

void  get_y_velocity(y_velocity_t * y_velocity)
{
    read_register(Y_VELOCITY_ADDR, sizeof(*y_velocity), y_velocity->u8_y_velocity);
}

void get_h_velocity(h_velocity_t * h_velocity)
{
    read_register(H_VELOCITY_ADDR, sizeof(*h_velocity), h_velocity->u8_h_velocity);
}

void set_ticks_per_mm(ticks_per_mm_t * ticks_per_mm)
{
    write_register(TICKS_PER_MM_ADDR, ticks_per_mm->u8_ticks_per_mm);
}

void get_ticks_per_mm(ticks_per_mm_t * ticks_per_mm)
{
    read_register(TICKS_PER_MM_ADDR, sizeof(*ticks_per_mm), ticks_per_mm->u8_ticks_per_mm);
}

void set_x_offset(x_offset_t * x_offset)
{
    write_register(X_POD_OFFSET_ADDR, x_offset->u8_x_offset);
}

void set_y_offset(y_offset_t * y_offset)
{
    write_register(Y_POD_OFFSET_ADDR, y_offset->u8_y_offset);
}

void set_h_offset(h_offset_t * h_offset)
{
    write_register(YAW_OFFSET_ADDR, h_offset->u8_h_offset);
}

void get_x_offset(x_offset_t * x_offset)
{
    read_register(X_POD_OFFSET_ADDR, sizeof(*x_offset), x_offset->u8_x_offset);
}

void get_y_offset(y_offset_t * y_offset)
{
    read_register(Y_POD_OFFSET_ADDR, sizeof(*y_offset), y_offset->u8_y_offset);
}

void get_h_offset(h_offset_t * h_offset)
{
    read_register(YAW_OFFSET_ADDR, sizeof(*h_offset), h_offset->u8_h_offset);
}

void read_all(bulk_read_t * bulk_read)
{
    read_register(BULK_READ_ADDR, sizeof(*bulk_read), bulk_read->u8_bulk_read);
}

void write_register(uint8_t reg, uint8_t data[4])
{
    const uint8_t buff[5] = {reg, data[0], data[1], data[2], data[3]};
    if(i2c_write_data(&pinpoint_dev_handle, buff, sizeof(buff)))
        log_e("Failed to write data to PinPoint");
}

void read_register(uint8_t reg, size_t len, uint8_t *data)
{
    if(i2c_read_data(&pinpoint_dev_handle, &reg, sizeof(reg), data, len))
        log_e("Failed to read data from PinPoint");
}

uint32_t to_32_bit(const uint8_t byte[4])
{
    return (((uint32_t)(byte[3]) << 24) | ((uint32_t)(byte[2]) << 16) | ((uint16_t)(byte[1]) << 8) | (byte[0] << 0));
}
