#ifndef WIFI_HUB_H
#define WIFI_HUB_H

#include <WiFi.h>
#include "websockets.hpp"

extern Websocket websocket;

class EasyWiFi
{
    public:
        void initAcessPoint();
    private:
        void setBestChannel();
        void onEventWiFi(WiFiEvent_t event);
};

#endif