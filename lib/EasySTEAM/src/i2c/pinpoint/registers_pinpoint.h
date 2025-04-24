#ifndef REGISTERS_PINPOINT_H
#define REGISTERS_PINPOINT_H

#include <inttypes.h>
#include <float.h>

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
        u8 : 4;
    } device_status_bitmap;
    u8 device_status_u8;
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
};

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

#endif