#ifndef EasySTEAM_h
#define EasySTEAM_h

#include "stemOSBoard.h"

class EasySTEAM {
    private:
        static void stopAll();
        static void stopMotors();
        static void stopServos();
        static void stopSensors();
        friend class stemWiFi;
    public:
};

#endif

