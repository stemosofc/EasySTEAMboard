#include "Arduino.h"
#include "UserCode.h"
#include "stemWiFi.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_ipc.h>
#include "AraraConfig.h"
#include "Logs.h"
UserClass UserCode;
stemWiFi wifi;
TaskHandle_t handlerUserInit;
TaskHandle_t handlerUserLoop;


void DISABLE() {
  for(int i = 0; i <= Portas.QuantPortas; i++) {
    ledcWrite(i, LOW);
  }
}


void initUser(void * arg) {
  UserCode.init();
  vTaskDelete(NULL);
}

void loopUser(void * arg) {
  TickType_t delay = 500 / portTICK_PERIOD_MS;
  vTaskDelay(delay);
  while(1) {
      UserCode.loop();
  }
}

void saveLog(void * arg) {
  Logs logs = Logs();

  
  for(int i = 0; i < 28; i++) {
    _debug_info.backtrace[i];
  }
  

  vTaskDelete(NULL);
}

void setup() {
  Serial.begin(115200);
  #if CONFIG_RESTART_DEBUG_INFO
    esp_register_shutdown_handler(debugUpdate);
  #endif 

  ::xTaskCreatePinnedToCore(saveLog, "Logs", 5000, NULL, 4, NULL, tskNO_AFFINITY);

  wifi.configureWiFiAP();

  ::xTaskCreatePinnedToCore(initUser, "InitUser", 5000, NULL, 2, &handlerUserInit, tskNO_AFFINITY);
  ::xTaskCreatePinnedToCore(loopUser, "LoopUser", 10000, NULL, 2, &handlerUserLoop, tskNO_AFFINITY);
}


void loop() {

}


