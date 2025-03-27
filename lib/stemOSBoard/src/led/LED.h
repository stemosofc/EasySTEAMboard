#pragma once

#include "Arduino.h"
#include "Freenove_WS2812_Lib_for_ESP32.h"
#include <bits/stdc++.h>

struct {
  const std::vector<int> AZUL = {0, 0, 128};
  const std::vector<int> VERMELHO = {255, 0, 0};
  const std::vector<int> AMARELO = {255, 215, 0};
  const std::vector<int> VERDE = 	{0, 255, 0};
  const std::vector<int> ROXO = {139, 0, 139};
  const std::vector<int> EMPTY = {0, 0, 0};
  const int SLOW_DELAY = 500;
  const int FAST_DELAY = 250;
} Colors;


class LED {
private:
  friend class stemWiFi;
  static const int PINO = 12;         // Pino GPIO do LED
  static const int CHANNEL = 11;       // Canal PWM
  static const int LEDS_COUNT = 1;
  static bool BLINK;
  static int DELAY_MS;
  static std::vector<int> cor1;
  static std::vector<int> cor2;
  static void CONFIGURE_WIFI_THREAD(void * arg);
  static void Blink_Action(void * arg);
  static void setColor(const std::vector<int> color1, const std::vector<int> color2, int delayMicroSeconds=DELAY_MS, bool blink=BLINK);
  static TaskHandle_t LED_HANDLER;
  static Freenove_ESP32_WS2812 fita;
  static void activateLED(const std::vector<int> colors);         
  static void init();
  static void ERRO();             // Sinaliza erro no código (Vermelho)
  static void CONFIGURE_WIFI();  // Acesso enquanto estivermos configurando WiFi
  static void OK();             // Quando tudo estiver correto
  static void NO_DS();
  static void Check(TaskHandle_t &task, const char * taskName);
  static bool stop;
};