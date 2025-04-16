#ifndef _MASTER_h_
#define _MASTER_h_

#define DEBUG 0

#include <inttypes.h>
#include "driver/gpio.h"
#include "esp32-hal-log.h"
#include "Arduino.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

extern bool DS_ENABLE;
extern bool ACTUATORS_ENABLE;

#endif