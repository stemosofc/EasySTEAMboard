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
  private:
    int id = -1;
    const  char* ssid = "Arara_";
    const char* password = "password";
    AsyncWebServer * server;
    AsyncWebSocket * ws;
    JsonDocument handleReceivedMessage(String message);
    void init();
    void setChannel();
    void errorJson(DeserializationError error);
    Gamepad joystick;
    void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
                void *arg, uint8_t *data, size_t len);
    void onEventWiFi(WiFiEvent_t event);
    void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
  };

#endif