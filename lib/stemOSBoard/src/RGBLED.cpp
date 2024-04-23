#include "RGBLED.h"

RGBLED::RGBLED() {

}

void RGBLED::init() {
  fita.begin();
	fita.setBrightness(10);	
}

void RGBLED::ERRO() {
  fita.setAllLedsColorData(VERMELHO[0], VERMELHO[1], VERMELHO[2]);
  fita.show();
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