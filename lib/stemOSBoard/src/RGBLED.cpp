#include "RGBLED.h"

Freenove_ESP32_WS2812 RGBLED::fita = Freenove_ESP32_WS2812(LEDS_COUNT, PINO, CHANNEL, TYPE_GRB);

TaskHandle_t RGBLED::LED_HANDLER = NULL;

void RGBLED::init() {
  fita.begin();
	fita.setBrightness(10);	
}

void RGBLED::ERRO() {
  fita.setAllLedsColorData(Colors.VERMELHO[0], Colors.VERMELHO[1], Colors.VERMELHO[2]);
  fita.show();
}

void RGBLED::CONFIGURE_WIFI() {
  fita.setAllLedsColor(Colors.ROXO[0], Colors.ROXO[1], Colors.ROXO[2]);
}

void RGBLED::NO_DS() {
  TaskHandle_t task = NULL;
  ::xTaskCreatePinnedToCore(CONFIGURE_WIFI_THREAD, "CONFIGURE WIFI", 1000, NULL, 2, &task, tskNO_AFFINITY);
  LED_HANDLER = task;
}

void RGBLED::OK() {
  if(LED_HANDLER != NULL) {
    vTaskDelete(LED_HANDLER);
    LED_HANDLER = NULL;
  }
  fita.setAllLedsColor(Colors.VERDE[0], Colors.VERDE[1], Colors.VERDE[2]);
}

void RGBLED::setColor(int cor[3]) {
  fita.setAllLedsColor(cor[0], cor[1], cor[2]);
}

void RGBLED::CONFIGURE_WIFI_THREAD(void * arg) {
  TickType_t delay = 500 / portTICK_PERIOD_MS;
  while(1) {
    fita.setAllLedsColorData(Colors.AZUL[0], Colors.AZUL[1], Colors.AZUL[2]);
    fita.show();
    vTaskDelay(delay);
    fita.setAllLedsColor(Colors.AMARELO[0], Colors.AMARELO[1], Colors.AMARELO[2]);
    vTaskDelay(delay);
  }
}