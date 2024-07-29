#include "stemWiFi.h"

stemWiFi::stemWiFi() {

}

void stemWiFi::init() {
    server = new AsyncWebServer(80);
    ws = new AsyncWebSocket("/ws");
    ws->onEvent(std::bind(&stemWiFi::onEvent, this
      , std::placeholders::_1
      , std::placeholders::_2
      , std::placeholders::_3
      , std::placeholders::_4
      , std::placeholders::_5
      , std::placeholders::_6));
    server->addHandler(ws);
    server->begin();
}

void stemWiFi::start() {
  RGBLED::init();
  RGBLED::CONFIGURE_WIFI();

  WiFi.onEvent(std::bind(&stemWiFi::onEventWiFi, this, std::placeholders::_1));

  setChannel();

  init();
  
  RGBLED::NO_DS();
}

void stemWiFi::setChannel() {
  int n = WiFi.scanNetworks();
  if (n == 0) {
    log_d("no networks found");
  } else {
      int canais[n];
      int canaisFix[14] = {};
      log_d("networks found");
      for (int i = 0; i < n; ++i) {
          canais[i] = WiFi.channel(i);
          canaisFix[canais[i]]++;
      }
      int low = 20;
      int channel = 1;
      for(int i = 1; i < 14; i++) {
        if(canaisFix[i] < low) {
          channel = i;
          low = canaisFix[i];
        }
      }
  WiFi.softAP(ssid + WiFi.macAddress(), password, channel);
  }
}

JsonDocument stemWiFi::handleReceivedMessage(String message) {
  JsonDocument jon;                
  deserializeJson(jon, message); 
  DeserializationError err = deserializeJson(jon, message);
  errorJson(err);

  return jon;
}


void stemWiFi::errorJson(DeserializationError err) {
  switch (err.code()) { 
      case DeserializationError::InvalidInput:
          log_e("Invalid input!");
          break;
      case DeserializationError::NoMemory:
          log_e("Not enough memory");
          break;
      case DeserializationError::Ok:
          break;
  }
}

void stemWiFi::onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
 void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      id = client->id();
      log_d("WebSocket client connected");
      RGBLED::OK();
      break;
    case WS_EVT_DISCONNECT:
      log_d("WebSocket client disconnected");
      RGBLED::NO_DS();
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
      break;
    case WS_EVT_ERROR:
      RGBLED::ERRO();
      break;
  }
}

void stemWiFi::onEventWiFi(WiFiEvent_t event){
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
            if(ws->hasClient(id)) {
              ws->closeAll(); 
              RGBLED::ERRO();   
            }
            break;
        case ARDUINO_EVENT_WIFI_AP_STAIPASSIGNED:
            break;
        default: break;
    }
}

void stemWiFi::handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    JsonDocument jon;              
    DeserializationError err = deserializeJson(jon, data);
    errorJson(err);
    Gamepad::gamepad = jon;
  }
}


