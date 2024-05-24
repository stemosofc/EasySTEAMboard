#ifndef RGBLED_h
#define RGBLED_h
#include "Arduino.h"
#include "Freenove_WS2812_Lib_for_ESP32.h"

struct {
  const int AZUL[3] = {0, 0, 128};
  const int VERMELHO[3] = {255, 0, 0};
  const int AMARELO[3] = {255, 215, 0};
  const int VERDE[3] = 	{0, 255, 0};
  const int ROXO[3] = {139, 0, 139};
} Colors;


class RGBLED {
public:
  static void configureLED(); 
  static void setColor(int cor[3]);         
  static void init();
  static void ERRO();             // Sinaliza erro no código (Vermelho)
  static void CONFIGURE_WIFI();  // Acesso enquanto estivermos configurando WiFi
  static void OK();             // Quando tudo estiver correto
  static void NO_DS();
private:
  static const int PINO = 12;         // Pino GPIO do LED
  static const int CHANNEL = 11;       // Canal PWM
  static const int LEDS_COUNT = 8;
  static void CONFIGURE_WIFI_THREAD(void * arg);
  static TaskHandle_t LED_HANDLER;
  static Freenove_ESP32_WS2812 fita;
};
#endif