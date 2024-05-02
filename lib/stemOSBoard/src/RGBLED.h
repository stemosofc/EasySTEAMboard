#ifndef RGBLED_h
#define RGBLED_h
#include "Arduino.h"
#include "Freenove_WS2812_Lib_for_ESP32.h"

class RGBLED {
public:
  RGBLED(void);
  void configureLED();    // Aqui configuramos o led (chamada no .ino)
  void setColor(int cor[3]);         // Quando tudo estiver correto
  void init();
  void ERRO();            // Sinaliza erro no código (Vermelho e preto)
  void CONFIGURE_WIFI();  // Acesso enquanto estivermos configurando WiFi
  void OK();   
private:
  static const int PINO = 12;         // Pino GPIO do LED
  static const int CHANNEL = 0;       // Canal PWM
  static const int LEDS_COUNT = 8;
  int AZUL[3] = {0, 0, 128};
  int VERMELHO[3] = {0, 0, 255};
  int AMARELO[3] = {255,215,0};
  int VERDE[3] = 	{0,255,0};
  static Freenove_ESP32_WS2812 fita;
};
#endif