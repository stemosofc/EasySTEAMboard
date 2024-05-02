#include "RGBLED.h"
#include "Thread.h"

Freenove_ESP32_WS2812 RGBLED::fita = Freenove_ESP32_WS2812(LEDS_COUNT, PINO, CHANNEL, TYPE_GRB);

RGBLED::RGBLED() {

}

void RGBLED::init() {
  fita.begin();
	fita.setBrightness(10);	
}

void RGBLED::ERRO() {
  fita.setAllLedsColorData(VERMELHO[0], VERMELHO[1], VERMELHO[2]);
}

void RGBLED::CONFIGURE_WIFI() {
  fita.setAllLedsColorData(AZUL[0], AZUL[1], AZUL[2]);
  fita.show();
}

void RGBLED::OK() {
  fita.setAllLedsColor(VERDE[0], VERDE[1], VERDE[2]);
}

void RGBLED::setColor(int cor[3]) {
  fita.setAllLedsColor(cor[0], cor[1], cor[2]);
}