#ifndef DRIVER_PINPOINT_H
#define DRIVER_PINPOINT_H

#include <stdbool.h>
#include <math.h>
#include "registers_pinpoint.h"

#include "driver_pinpoint.h"
#include "i2c/i2c_driver.h"

void init_pinpoint_i2c(void);
bool pinpoint_is_connected(void);

uint32_t get_device_id(void);

uint32_t get_device_version(void);

void get_device_status(device_status_t * device_status);

void set_device_control(device_control_t * device_control);

uint32_t get_loop_time_us(void);

double get_frequency(void);

uint32_t get_raw_x_encoder(void);

uint32_t get_raw_y_encoder(void);

void get_x_position(x_position_t * x_pose);

void get_y_position(y_position_t * y_pose);

void get_heading(h_orientation_t * heading);

void set_x_position(x_position_t * x_position);

void set_y_position(y_position_t * y_position);

void set_heading(h_orientation_t * orientation);

void get_x_velocity(x_velocity_t * x_velocity);

void  get_y_velocity(y_velocity_t * y_velocity);

void get_h_velocity(h_velocity_t * h_velocity);

void set_ticks_per_mm(ticks_per_mm_t * ticks_per_mm);

void get_ticks_per_mm(ticks_per_mm_t * ticks_per_mm);

void set_x_offset(x_offset_t * x_offset);

void set_y_offset(y_offset_t * y_offset);

void set_h_offset(h_offset_t * h_offset);

void get_x_offset(x_offset_t * x_offset);

void get_y_offset(y_offset_t * y_offset);

void get_h_offset(h_offset_t * h_offset);

void read_all(bulk_read_t * bulk_read);

void write_register(uint8_t reg, uint8_t data[4]);

void read_register(uint8_t reg, size_t len, uint8_t *data);

uint32_t to_32_bit(const uint8_t byte[4]);

#endif