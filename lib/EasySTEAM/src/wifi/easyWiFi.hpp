#ifndef EASY_WIFI_H_
#define EASY_WIFI_H_

#include <WiFi.h>
#include <ArduinoJson.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "gamepad/Gamepad.h"
#include "master.h"
class stemWiFi {
  public:
    void start();
  private:
    int id = -1;
    AsyncWebServer * server;
    AsyncWebSocket * ws;
    JsonDocument handleReceivedMessage(String message);
    void initWebServer();
    void setChannel();
    void disconnectWebsocketClients(bool error=false);
    void disableActuators();
    void errorJson(DeserializationError error);
    void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
                void *arg, uint8_t *data, size_t len);
    void onEventWiFi(WiFiEvent_t event);
    void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
};

#endif