#include "RGBLED.h"

RGBLED::RGBLED() {

}

void RGBLED::ERRO() {
  fita.begin();
	fita.setBrightness(10);	
}

void RGBLED::CONFIGURE_WIFI() {
  fita.setAllLedsColor(AMARELO[0], AMARELO[1], AMARELO[2]);
  delay(30);
  fita.setAllLedsColorData(AZUL[0], AZUL[1], AZUL[2]);
  delay(30);
}

void RGBLED::OK() {
  fita.setAllLedsColor(VERDE[0], VERDE[1], VERDE[2]);
}
void RGBLED::setColor(int cor[3]) {
  fita.setAllLedsColor(cor[0], cor[1], cor[2]);
}