#ifndef PINPOINT_H
#define PINPOINT_H

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
    private:
        float xPose;
        float yPose;
        float wPose;
        float xVelocity;
        float yVelocity;
        float wVelocity;
        void defaultInit();
        void setTicksPerMM();
        void update();
        int getLoopTime();
        void restartPinPoint();
};

#endif