#pragma once
#include "Arduino.h"
#include <WiFi.h>
#include <ArduinoJson.h>
#include "LED.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "esp32-hal-log.h"
#include "Gamepad.h"
#include "Objects.h"

class stemWiFi {
  public:
    stemWiFi(void);
    void start();
  private:
    int id = -1;
    const  char* ssid = "EasySTEAM_";
    const char* password = "password";
    const int TIMEOUT_DELAY = 100;
    AsyncWebServer * server;
    AsyncWebSocket * ws;
    JsonDocument handleReceivedMessage(String message);
    void initWebServer();
    void setChannel();
    void disconnect(bool error=false);
    void errorJson(DeserializationError error);
    void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
                void *arg, uint8_t *data, size_t len);
    void onEventWiFi(WiFiEvent_t event);
    void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
    int previousTime = 0;
    bool previousGamepadState = false;
    int count = 0;
    int delay[5];
    Control control;
};