#include "wifi.hpp"

#ifdef __cplusplus
extern "C" 
{
#endif

#include "ping_ll.h"

#ifdef __cplusplus
}
#endif


const  char* ssid = "EasySTEAM_";
const char* password = "password";

Websocket websocket;

void EasyWiFi::initAcessPoint()
{
    WiFi.onEvent(std::bind(&EasyWiFi::onEventWiFi, this, std::placeholders::_1));

    setBestChannel();
}

void EasyWiFi::setBestChannel() {
    int n = WiFi.scanNetworks();
    int channel = 1;
    if (n > 0) {
        int canais[n];
        int canaisFix[14] = {};
        log_d("%d networks found", n);
        for (int i = 0; i < n; ++i) {
            canais[i] = WiFi.channel(i);
            canaisFix[canais[i]]++;
        }
        int low = 1e7;
        for(int i = 1; i < 14; i++) 
        {
            if(canaisFix[i] < low) 
            {
                channel = i;
                low = canaisFix[i];
            }
        }
        log_d("The best channel is: %d", channel);
    }
    if(!WiFi.softAP(ssid + WiFi.macAddress(), password, channel)) 
        log_e("Init AP error");
}


void EasyWiFi::onEventWiFi(WiFiEvent_t event)
{
    switch (event) {
        case ARDUINO_EVENT_WIFI_READY: 
            break;
        case ARDUINO_EVENT_WIFI_SCAN_DONE:
            log_d("Scan Done");
            break;
        case ARDUINO_EVENT_WIFI_AP_START:
            break;
        case ARDUINO_EVENT_WIFI_AP_STOP:
            break;
        case ARDUINO_EVENT_WIFI_AP_STACONNECTED:
            break;
        case ARDUINO_EVENT_WIFI_AP_STADISCONNECTED:
            stop_ping_session();
            if(websocket.hasClients()) 
            {
                websocket.disconnectWebsocketClients(true);
                log_e("Disconnecting clients");
            }
            break;
        case ARDUINO_EVENT_WIFI_AP_STAIPASSIGNED:
            start_ping_session();
            break;
        default: break;
    }
}