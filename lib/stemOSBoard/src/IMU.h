#include "Arduino.h"
#include "ICM_20948.h"
#include "esp32-hal-log.h"
#include "Task.h"

#define WIRE_PORT Wire;

class IMU : public Task {
    public:
        void init(void);
        double getYaw();
        double getRoll();
        double getPitch();
        void calcule();
        void run(void * data) {
            calcule();
        }
    private:
        ICM_20948_I2C myICM;
        const int AD0_VAL = 0;
        void update(void * arg);
        double q2sqr;
        double q0;
        double q1;
        double q2;
        double q3;
        double q4;
};