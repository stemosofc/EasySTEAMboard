#ifndef DRIVER_PINPOINT_H
#define DRIVER_PINPOINT_H

#include "registers_pinpoint.h"

void start(void);
device_status_t get_device_status(void);
uint32_t get_device_version(void);

void set_device_control();

uint32_t get_loop_time(void);

uint32_t get_raw_x_encoder(void);
uint32_t get_raw_y_encoder(void);

x_position_t get_x_position(void);
y_position_t get_y_position(void);
h_orientation_t get_heading(void);
void set_x_position(x_position_t x_position);
void set_y_position(y_position_t y_position);
void set_heading(h_orientation_t orientation);

x_velocity_t get_x_velocity(void);
y_velocity_t get_y_velocity(void);
h_velocity_t get_h_velocity(void);

float get_ticks_per_mm(void);

void set_x_offset(float offset);
void set_y_offset(float offset);
void set_h_offset(float offset);
float get_x_offset(void);
float get_y_offset(void);
float get_h_offset(void);

double read_all(void);

#endif