#ifndef _MASTER_h_
#define _MASTER_h_

#ifdef __cplusplus
extern "C"
{
#endif

#include <inttypes.h>
#include <stdbool.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>

extern bool DS_ENABLE;
extern bool ACTUATORS_ENABLE;
#ifdef __cplusplus
}
#endif

#include "esp32-hal-log.h"

#define SKIP_DRIVERSTATION_ENABLE 0
#define DEBUG_PING_ENABLE 0

#endif