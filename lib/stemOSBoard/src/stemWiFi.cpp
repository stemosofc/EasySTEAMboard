#include "stemWiFi.h"
RGBLED led;

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

void stemWiFi::configureWiFiAP() {
  led.init();
  //RGBLED::configureLED();
  log_i("Definindo modo WiFi", WiFi.mode(WIFI_AP));

  log_i("Iniciando Acess Point", WiFi.softAP(ssid, password));

  log_i("Endereço IP");
  if(Serial) {
    Serial.println(WiFi.softAPIP());
  }

  init();

  delay(500);
  
  led.CONFIGURE_WIFI();
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
      Serial.println("WebSocket client connected");
      led.OK();
      break;
    case WS_EVT_DISCONNECT:
      Serial.println("WebSocket client disconnected");
      led.CONFIGURE_WIFI();
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
      break;
    case WS_EVT_ERROR:
      led.ERRO();
      break;
  }
}

void stemWiFi::cleanupClients() {
  ws->cleanupClients();
}

void stemWiFi::handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    JsonDocument jon;                
    DeserializationError err = deserializeJson(jon, data);
    errorJson(err);
    String state = jon["Estado"]; // BUG do vscode?
    this->state = state;
    Gamepad::gamepad = jon;
  }
}

