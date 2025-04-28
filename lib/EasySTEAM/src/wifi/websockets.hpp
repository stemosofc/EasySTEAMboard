#ifndef WEBSOCKETS_H
#define WEBSOCKETS_H

#include "master.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "gamepad/Gamepad.h"
#include "led/LED.hpp"
#include "websockets.hpp"

class Websocket
{
    public:
        void initWebServer();
        void disconnectWebsocketClients(bool error=false);
        bool hasClients();
    private:
        int id = -1;
        AsyncWebServer * server;
        AsyncWebSocket * ws;
        JsonDocument handleReceivedMessage(String message);
        void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
        void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
        void errorJson(DeserializationError error);

};

#endif