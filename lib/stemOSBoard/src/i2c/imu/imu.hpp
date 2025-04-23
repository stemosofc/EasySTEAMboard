#ifndef IMU_h
#define IMU_h

#include "Task.hpp"

#ifdef __cplusplus
extern "C" {
#endif
    #include "imu_driver/icm20948_config_driver_i2c.h"
    #include "imu_driver/icm20948_i2c.h"
    #include <math.h>
#ifdef __cplusplus
}
#endif

class IMU : public Task
{
    public:
        void start(void);
        double getYaw(void);
        double getPitch(void);
        double getRoll(void);

    private:
        void calc(void);
        void defaultStartup(void);
        void init_dmp(icm20948_device_t *icm);
        void run(void * data)
        {
            calc();
        }
        static bool alreadyCreated;
        double qw = 0;
        double qx = 0;
        double qy = 0;
        double qz = 0;
};

#endif