#include "Arduino.h"
#include "UserCode.h"
#include "stemWiFi.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_ipc.h>
#include "AraraConfig.h"

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

void setup() {
  Serial.begin(115200);

  wifi.configureWiFiAP();

  ::xTaskCreatePinnedToCore(initUser, "InitUser", 5000, NULL, 2, &handlerUserInit, tskNO_AFFINITY);
  ::xTaskCreatePinnedToCore(loopUser, "LoopUser", 10000, NULL, 2, &handlerUserLoop, tskNO_AFFINITY);
}


void loop() {

}


