#ifndef stemOSboard_h
#define stemOSboard_h
#include "Arduino.h"
#include "Motor.h"
#include "stemWiFi.h"
#include "Gamepad.h"
#include "Digital.h"
#include "ServoOS.h"
#include "Analog.h"
#include "RGBLED.h"
#include "IMU.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_ipc.h>

class Arara {
    private:
    public:
        virtual void init() = 0;
        virtual void loop() = 0;
};

#endif
