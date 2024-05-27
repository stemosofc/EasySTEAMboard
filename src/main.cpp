#include "Arduino.h"
#include "UserCode.h"
#include "stemWiFi.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_ipc.h>
#include "AraraConfig.h"
#include "esp_check.h"
#include "esp_err.h"
#include "esp_debug_helpers.h"

UserClass UserCode;
stemWiFi wifi;
TaskHandle_t handlerUser;

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


void setup() {
  Serial.begin(115200);
  wifi.configureWiFiAP();
  ::xTaskCreatePinnedToCore(initUser, "InitUser", 5000, NULL, 4, &handlerUser, tskNO_AFFINITY);
  ::xTaskCreatePinnedToCore(loopUser, "LoopUser", 10000, NULL, 4, &handlerUser, tskNO_AFFINITY);
}

void DISABLE() {
  for(int i = 0; i <= QuantPortas; i++) {
    digitalWrite(i, LOW);
  }
}

void loop() {
  String estado = wifi.estado["Estado"];
  if(estado == "Habilitado") {
    vTaskResume(handlerUser);
  } else {
    vTaskSuspend(handlerUser);
    DISABLE();
  }
}


