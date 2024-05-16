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
    JsonDocument handleReceivedMessage(String message);
    bool waitForStart();
    void cleanupClients();
    String state = "Desabilitado";
  private:
    long int PrevTime = 0;
    long int tempo = 0;
    long int diffTempo = 0;
    int c = 0;
    const  char* ssid = "AraraScan";
    const char* password = "BlueStemOS";
    AsyncWebServer * server;
    AsyncWebSocket * ws;
    void init();
    static void sendRSSI(void * arg);
    void initSendRSSI();
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