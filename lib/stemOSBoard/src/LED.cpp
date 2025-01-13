#include "LED.h"

Freenove_ESP32_WS2812 LED::fita = Freenove_ESP32_WS2812(LEDS_COUNT, PINO, CHANNEL, TYPE_GRB);

TaskHandle_t LED::LED_HANDLER = NULL;

bool LED::BLINK = false;
int LED::DELAY_MS = 500;
bool LED::stop = false;
std::vector<int> LED::cor1 = {Colors.EMPTY};
std::vector<int> LED::cor2 = {Colors.EMPTY};

void LED::init() {
  fita.begin();
}

void LED::ERRO() {
  setColor(Colors.VERMELHO, Colors.EMPTY, 0,  false);
}

void LED::CONFIGURE_WIFI() {
  setColor(Colors.ROXO, Colors.EMPTY, 0, false);
}

void LED::NO_DS() {
  setColor(Colors.AZUL, Colors.AMARELO, Colors.SLOW_DELAY, true);
}

void LED::OK() {
  setColor(Colors.VERDE, Colors.EMPTY, 0, false);
}

/*
void LED::CONFIGURE_WIFI_THREAD(void * arg) {
  TickType_t delay = 500 / portTICK_PERIOD_MS;
  while(1) {
    setColor(Colors.AZUL);
    vTaskDelay(delay);
    setColor(Colors.AMARELO);
    vTaskDelay(delay);
  }
}
*/

void LED::activateLED(std::vector<int> cor) {
  fita.setAllLedsColor(cor[0], cor[1], cor[2]);
}

void LED::setColor(const std::vector<int> color1, const std::vector<int> color2, int delayMicroSeconds, bool blink) {
  stop = true;
  BLINK = blink;
  DELAY_MS = delayMicroSeconds;
  cor1 = color1;
  cor2 = color2;

  TaskHandle_t task = NULL;
  xTaskCreatePinnedToCore(Blink_Action, "LED", 1000, NULL, 2, &task, tskNO_AFFINITY);
}

void LED::Blink_Action(void * arg) { 
  stop = false;
  const TickType_t delay = DELAY_MS / portTICK_PERIOD_MS;

  while(1) {
    if(!BLINK) {
      activateLED(cor1); 
      vTaskDelete(NULL);
    } else if(!stop) {
      activateLED(cor1);
      vTaskDelay(delay);
      activateLED(cor2);
      vTaskDelay(delay);
  } else {
    vTaskDelete(NULL);
    }
  }
}

