#include "pinpoint.hpp"

#ifdef __cplusplus
extern "C"
{
#endif
#include "driver_pinpoint.h"

device_status_t device_status = {.device_status_u32 = 0U};
device_control_t device_control = {.device_control_u8 = 0U};
x_position_t x_pose = {.f32_x_position = 0.0f};
y_position_t y_pose = {.f32_y_position = 0.0f};
h_orientation_t w_pose = {.f32_heading = 0.0f};
x_velocity_t x_velocity = {.f32_x_velocity = 0.0f};
y_velocity_t y_velocity = {.f32_y_velocity = 0.0f};
h_velocity_t w_velocity = {.f32_h_velocity = 0.0f};
x_offset_t x_offset = {.f32_x_offset = 0.0f};
y_offset_t y_offset = {.f32_y_offset = 0.0f};
h_offset_t h_offset = {.f32_h_offset = 0.0f};
loop_time_t loop_time = {.u32_loop_time = 0U};
bulk_read_t bulk_read = {.u8_bulk_read = {0}};

#ifdef __cplusplus
}
#endif



void PinPoint::start()
{
    init_pinpoint_i2c();
}

void PinPoint::defaultInit()
{
    
}
