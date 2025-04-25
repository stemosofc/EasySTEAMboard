#include "pinpoint.hpp"

#ifdef __cplusplus
extern "C"
{
#endif
#include "driver_pinpoint.h"

device_status_t device_status = {.device_status_u32 = 0U};
device_control_t device_control = {.device_control_u32 = 0U};
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
ticks_per_mm_t ticks_per_mm = {.f32_ticks_per_mm = 0.0f};
x_raw_encoder_t x_raw = {.u32_x_raw_encoder = 0.0f};
y_raw_encoder_t y_raw = {.u32_y_raw_encoder = 0.0f};

#ifdef __cplusplus
}
#endif

#define TICKS_PER_MM_SWINGARM_POD 13.26291192f
#define TICKS_PER_MM_4_BAR_POD 19.89436789f

void PinPoint::start()
{
    init_pinpoint_i2c();
}

bool PinPoint::isConnected()
{
    return pinpoint_is_connected();
}

void PinPoint::defaultInit()
{
    if(!pinpoint_is_connected())
    {
        log_e("PinPoint don't connected, try again!");
        return;
    }

    setResolutionForOdometryPod(PODS::goBILDA_4_BAR_POD);

    setEncoderDirection(DIRECTION::FORWARD, DIRECTION::FORWARD);

    resetIMUAndPose();

    while(!isConnected()){}

    log_i("Device Version: %d", getDeviceVersion());
    log_i("Device ID: %d", getDeviceID());
}

void PinPoint::setResolutionForOdometryPod(PODS pods)
{
    float resolution = 0.0f;
    if(pods == PODS::goBILDA_4_BAR_POD) resolution = TICKS_PER_MM_SWINGARM_POD;
    if(pods == PODS::goBILDA_SWINGARM_POD) resolution = TICKS_PER_MM_4_BAR_POD;
    setResolutionForOdometryPod(resolution);
}

void PinPoint::setResolutionForOdometryPod(float resolution)
{
    ticks_per_mm.f32_ticks_per_mm = resolution;
    set_ticks_per_mm(&ticks_per_mm);
}

void PinPoint::setEncoderDirection(DIRECTION podXDirection, DIRECTION podYDirection)
{
    device_control.device_control_bitmap = {0};
    if(podXDirection == DIRECTION::FORWARD) device_control.device_control_bitmap.__X_ENCODER_FORWARD = 1;
    if(podXDirection == DIRECTION::REVERSE) device_control.device_control_bitmap.__X_ENCODER_REVERSED = 1;
    if(podYDirection == DIRECTION::FORWARD) device_control.device_control_bitmap.__Y_ENCODER_FORWARD = 1;
    if(podYDirection == DIRECTION::REVERSE) device_control.device_control_bitmap.__Y_ENCODER_REVERSED = 1;

    set_device_control(&device_control);
}

void PinPoint::resetIMU()
{
    device_control.device_control_bitmap.__RESET_IMU = 1;
    set_device_control(&device_control);
}

void PinPoint::resetIMUAndPose()
{
    device_control.device_control_bitmap.__RESET_IMU_AND_POSITION = 1;
    set_device_control(&device_control);
}

int PinPoint::getDeviceVersion()
{
    return get_device_version();
}

int PinPoint::getDeviceID()
{
    return get_device_id();
}

int PinPoint::getDeviceStatus()
{
    return device_status.device_status_u32;
}

float PinPoint::getXPose()
{
    xPose = x_pose.f32_x_position;
    return xPose;
}

float PinPoint::getYPose()
{
    yPose = y_pose.f32_y_position;
    return yPose;
}

float PinPoint::getYaw()
{
    wPose = w_pose.f32_heading;
    return wPose;
}

void PinPoint::setPose(float xPose, float yPose, float yaw)
{
    x_pose.f32_x_position = xPose;
    y_pose.f32_y_position = yPose;
    w_pose.f32_heading = yaw;

    set_x_position(&x_pose);
    set_y_position(&y_pose);
    set_heading(&w_pose);
}

float PinPoint::getXVelocity()
{
    xVelocity = x_velocity.f32_x_velocity;
    return xVelocity;
}

float PinPoint::getYVelocity()
{
    yVelocity = y_velocity.f32_y_velocity;
    return yVelocity;
}

float PinPoint::getOmegaVelocity()
{
    wVelocity = w_velocity.f32_h_velocity;
    return wVelocity;
}

int PinPoint::getXEncoderValue()
{
    return x_raw.u32_x_raw_encoder;
}

int PinPoint::getYEncoderValue()
{
    return y_raw.u32_y_raw_encoder;
}

int PinPoint::getLoopTime()
{
    return loop_time.u32_loop_time;
}

float PinPoint::getFrequency()
{
    return get_frequency();
}

void PinPoint::update()
{
    read_all(&bulk_read);

    device_status = bulk_read.bulk_read_obj.device_status;
    loop_time = bulk_read.bulk_read_obj.loop_time;
    x_pose = bulk_read.bulk_read_obj.x_pose;
    y_pose = bulk_read.bulk_read_obj.y_pose;
    w_pose = bulk_read.bulk_read_obj.h_orientation;
    x_velocity = bulk_read.bulk_read_obj.x_velocity;
    y_velocity = bulk_read.bulk_read_obj.y_velocity;
    w_velocity = bulk_read.bulk_read_obj.h_velocity;
    x_raw = bulk_read.bulk_read_obj.x_raw_value;
    y_raw = bulk_read.bulk_read_obj.y_raw_value;
}
