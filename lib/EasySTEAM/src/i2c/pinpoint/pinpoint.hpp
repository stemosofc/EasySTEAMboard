#ifndef PINPOINT_H
#define PINPOINT_H

enum PODS
{
    goBILDA_4_BAR_POD,
    goBILDA_SWINGARM_POD,
};

enum DIRECTION
{
    FORWARD,
    REVERSE,
};

class PinPoint
{   
    public:
        void start();
        float getXPose();
        float getYPose();
        float getYaw();
        float getXVelocity();
        float getYVelocity();
        float getOmegaVelocity();
        void setPose(float xPose, float yPose, float yaw);
        bool isConnected();
        void setResolutionForOdometryPod(PODS pod);
        void setResolutionForOdometryPod(float resolution);
        void setEncoderDirection(DIRECTION podXDirection, DIRECTION podYDirection);
        void resetIMU();
        void resetIMUAndPose();
        int getDeviceStatus(); 
        int getDeviceVersion();
        int getDeviceID();
        int getXEncoderValue();
        int getYEncoderValue();
        float getFrequency();
        int getLoopTime();
        void update();
    private:
        float xPose = 0;
        float yPose = 0;
        float wPose = 0;
        float xVelocity = 0;
        float yVelocity = 0;
        float wVelocity = 0;
        void defaultInit();
};

#endif