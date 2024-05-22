#include "stemOSBoard.h"
#include "UserCode.h"

UserClass UserCode;
stemWiFi wifi;
TaskHandle_t handlerUser;

void initUser(void * arg) {
  UserCode.init();
  vTaskDelete(NULL);
}

void loopUser(void * arg) {
  TickType_t delay = 20 / portTICK_PERIOD_MS;
  while(1) {
    UserCode.loop();
    vTaskDelay(delay);
  }
}


void setup() {
  Serial.begin(115200);

  wifi.configureWiFiAP();

  ::xTaskCreatePinnedToCore(initUser, "InitUser", 5000, NULL, 4, &handlerUser, tskNO_AFFINITY);
  ::xTaskCreatePinnedToCore(loopUser, "LoopUser", 10000, NULL, 4, &handlerUser, tskNO_AFFINITY);
}

void DISABLE() {
  for(int i = 0; i <= 10; i++) {
    ledcWrite(i, 0);
  }
}

void loop() {
  String estado = wifi.estado["Estado"];
  if(estado == "Habilitado") {
    vTaskResume(handlerUser);
  } else {
    vTaskSuspend(handlerUser);
    // DISABLE();
  }
}


