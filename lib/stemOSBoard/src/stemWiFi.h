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
    String getData();
    void sendData(String message);
    JsonDocument handleReceivedMessage(String message);
    void getGamepadValues();
    bool waitForStart();
    String getEnable();
    bool getClientConnected();
    void cleanupClients();
  private:
    const  char* ssid = "Arara";
    const char* password = "BlueStemOS";
    AsyncWebServer * server;
    AsyncWebSocket * ws;
    void init();
    // WiFiServer server;
    // WiFiClient client;
    void errorJson(DeserializationError error);
    Gamepad joystick;
    void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
                void *arg, uint8_t *data, size_t len);
    void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
    void loadingWiFi();
  };

#endif