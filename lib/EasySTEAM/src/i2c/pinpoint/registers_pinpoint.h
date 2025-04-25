#ifndef REGISTERS_PINPOINT_H
#define REGISTERS_PINPOINT_H

#include <inttypes.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;

#define PINPOINT_I2C_ADDRESS 0x31

//#define DEVICE_ID_VALUE 0x02
//#define DEVICE_VERSION_VALUE 0x01

#define DEVICE_ID_ADDR 1
#define DEVICE_VERSION_ADDR 2
#define DEVICE_STATUS_ADDR 3
#define DEVICE_CONTROL_ADDR 4
#define LOOP_TIME_ADDR 5
#define X_ENCODER_VALUE_ADDR 6
#define Y_ENCODER_VALUE_ADDR 7
#define X_POSITION_ADDR 8
#define Y_POSITION_ADDR 9
#define H_ORIENTATION_ADDR 10
#define X_VELOCITY_ADDR 11
#define Y_VELOCITY_ADDR 12
#define H_VELOCITY_ADDR 13
#define TICKS_PER_MM_ADDR 14
#define X_POD_OFFSET_ADDR 15
#define Y_POD_OFFSET_ADDR 16
#define YAW_OFFSET_ADDR 17
#define BULK_READ_ADDR 18

typedef union
{
    struct device_status_bitmap_t
    {
        u8 __READY : 1;
        u8 __CALIBRATING : 1;
        u8 __X_NOT_DETECTED : 1;
        u8 __Y_NOT_DETECTED : 1;
        u8 __FAULT_IMU_RUNAWAY : 1;
        u8 __FAULT_BAD_READ : 1;
        u8 : 2;
    } device_status_bitmap;
    u8 device_status_u8[4];
    u32 device_status_u32;
} device_status_t;

typedef union
{
    struct device_control_bitmap_t
    {
        u8 __RESET_IMU : 1;
        u8 __RESET_IMU_AND_POSITION : 1;
        u8 __Y_ENCODER_REVERSED : 1;
        u8 __Y_ENCODER_FORWARD : 1;
        u8 __X_ENCODER_REVERSED : 1;
        u8 __X_ENCODER_FORWARD : 1;
        u8 : 1;
        u8 : 1;
    } device_control_bitmap;
    u8 device_control_u8[4];
    u32 device_status_u32;
} device_control_t;

typedef union
{
    u32 u32_loop_time;
    u8 u8_loop_time[4];
} loop_time_t;


typedef union
{
    u32 u32_x_raw_encoder;
    u8  u8_x_raw_encoder[4];
} x_raw_encoder_t;

typedef union
{
    u32 u32_y_raw_encoder;
    u8  u8_y_raw_encoder[4];
} y_raw_encoder_t;


typedef union
{
    f32 f32_x_position;
    u8 u8_x_position[4];
} x_position_t;

typedef union
{
    f32 f32_y_position;
    u8 u8_y_position[4];
} y_position_t;

typedef union
{
    f32 f32_heading;
    u8 u8_heading[4];
} h_orientation_t;

typedef union
{
    f32 f32_x_velocity;
    u8 u8_x_velocity[4];
} x_velocity_t;

typedef union
{
    f32 f32_y_velocity;
    u8 u8_y_velocity[4];
} y_velocity_t;

typedef union
{
    f32 f32_h_velocity;
    u8 u8_h_velocity[4];
} h_velocity_t;

typedef union
{
    f32 f32_ticks_per_mm;
    u8 u8_ticks_per_mm[4];
} ticks_per_mm_t;

typedef union
{
    f32 f32_x_offset;
    u8 u8_x_offset[4];
} x_offset_t;

typedef union
{
    f32 f32_y_offset;
    u8 u8_y_offset[4];
} y_offset_t;

typedef union
{
    f32 f32_h_offset;
    u8 u8_h_offset[4];
} h_offset_t;

typedef union
{
    struct bulk_read_obj_t
    {
        device_status_t device_status;
        // looptime
        // x raw
        // y raw
        x_position_t x_pose;
        y_position_t y_pose;
        h_orientation_t h_orientation;
        x_velocity_t x_velocity;
        y_velocity_t y_velocity;
        h_velocity_t h_velocity;
    } bulk_read_obj;
    u8 u8_bulk_read[40];
} bulk_read_t;



#endif