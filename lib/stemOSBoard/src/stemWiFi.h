#ifndef stemWiFi_h
#define stemWiFi_h

#include "Arduino.h"
#include <WiFi.h>
#include <ArduinoJson.h>
#include "Gamepad.h"
#include "RGBLED.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "esp32-hal-log.h"

class stemWiFi {
  public:
    stemWiFi(void);
    void configureWiFiAP();
    String estado = "Desabilitado";
  private:
    const  char* ssid = "AraraBancada";
    const char* password = "password";
    int prevChannel = 0;
    AsyncWebServer * server;
    AsyncWebSocket * ws;
    JsonDocument handleReceivedMessage(String message);
    void cleanupClients();
    void init();
    void setChannel();
    static void sendRSSI(void * arg);
    void initSendRSSI();
    void errorJson(DeserializationError error);
    Gamepad joystick;
    void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
                void *arg, uint8_t *data, size_t len);
    void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
    void loadingWiFi();
  };

#endif