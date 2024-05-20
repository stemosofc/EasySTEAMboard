#include "RGBLED.h"

Freenove_ESP32_WS2812 RGBLED::fita = Freenove_ESP32_WS2812(LEDS_COUNT, PINO, CHANNEL, TYPE_GRB);

int RGBLED::AZUL[3] = {0, 0, 128};
int RGBLED::VERMELHO[3] = {0, 0, 255};
int RGBLED::AMARELO[3] = {255, 215, 0};
int RGBLED::VERDE[3] = 	{0, 255, 0};
int RGBLED::ROXO[3] = {139, 0, 139};

TaskHandle_t RGBLED::LED_HANDLER = NULL;

RGBLED::RGBLED() { 

}

void RGBLED::init() {
  fita.begin();
	fita.setBrightness(10);	
}

void RGBLED::ERRO() {
  if(LED_HANDLER != nullptr) {vTaskDelete(LED_HANDLER);}
  fita.setAllLedsColorData(VERMELHO[0], VERMELHO[1], VERMELHO[2]);
}

void RGBLED::CONFIGURE_WIFI() {
  fita.setAllLedsColor(ROXO[0], ROXO[1], ROXO[2]);
}

void RGBLED::NO_DS() {
  TaskHandle_t task = NULL;
  ::xTaskCreatePinnedToCore(CW, "CONFIGURE WIFI", 1000, NULL, 2, &task, tskNO_AFFINITY);
  LED_HANDLER = task;
}

void RGBLED::OK() {
  if(LED_HANDLER != NULL) {
    vTaskDelete(LED_HANDLER);
  }
  fita.setAllLedsColor(VERDE[0], VERDE[1], VERDE[2]);
}

void RGBLED::setColor(int cor[3]) {
  fita.setAllLedsColor(cor[0], cor[1], cor[2]);
}

void RGBLED::STOP() {

}

void RGBLED::CW(void * arg) {
  TickType_t delay = 500 / portTICK_PERIOD_MS;
  while(1) {
    fita.setAllLedsColorData(AZUL[0], AZUL[1], AZUL[2]);
    fita.show();
    vTaskDelay(delay);
    fita.setAllLedsColor(AMARELO[0], AMARELO[1], AMARELO[2]);
    vTaskDelay(delay);
  }
}