#ifndef _MASTER_h_
#define _MASTER_h_

#ifdef __cplusplus
extern "C"
{
#endif

#undef LOG_LOCAL_LEVEL
#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG

#include <inttypes.h>
#include <stdbool.h>
#include <driver/gpio.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>

extern bool DS_ENABLE;
extern bool ACTUATORS_ENABLE;
#ifdef __cplusplus
}
#endif


#endif