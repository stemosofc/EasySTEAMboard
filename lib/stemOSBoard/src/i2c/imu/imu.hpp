#ifndef IMU_h
#define IMU_h

#include "master.h"

extern "C"
{
    #include "imu_driver/icm20948_config_driver_i2c.h"
    #include "imu_driver/icm20948_i2c.h"
}

class IMU
{
    public:
        void start(void);
        double getYaw(void);
        double getPitch(void);
        double getRoll(void);
        void calc(void);
    private:
        void defaultStartup(void);
        void init_dmp(icm20948_device_t *icm);
        static bool alreadyCreated;
        double qw = 0;
        double qx = 0;
        double qy = 0;
        double qz = 0;
};

#endif