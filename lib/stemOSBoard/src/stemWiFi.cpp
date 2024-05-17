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

  setChannel();

  init();

  delay(500);
  
  led.CONFIGURE_WIFI();

  // ::xTaskCreatePinnedToCore(sendRSSI, "RSSI", 2000, NULL, 4, NULL, tskNO_AFFINITY);
}

void stemWiFi::setChannel() {
  int n = WiFi.scanNetworks();
  log_d("Scan done");
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
        int channel = 0;
        for(int i = 1; i < 14; i++) {
          if(canaisFix[i] < low) {
            channel = i;
            low = canaisFix[i];
          }
        }
        log_d("Iniciando AP", WiFi.softAP("Arara", "password", channel));
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
      log_d("WebSocket client connected");
      led.OK();
      break;
    case WS_EVT_DISCONNECT:
      ws->cleanupClients();
      log_d("WebSocket client disconnected");
      led.CONFIGURE_WIFI();
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
      log_d("Pong recebido");
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

  void stemWiFi::sendRSSI(void * arg) {
    while(1) {
    int n = WiFi.scanNetworks();
    Serial.println("Scan done");
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        Serial.println("Nr | SSID                             | RSSI | CH | Encryption");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.printf("%2d",i + 1);
            Serial.print(" | ");
            Serial.printf("%-32.32s", WiFi.SSID(i).c_str());
            Serial.print(" | ");
            Serial.printf("%4d", WiFi.RSSI(i));
            Serial.print(" | ");
            Serial.printf("%2d", WiFi.channel(i));
            Serial.print(" | ");
            switch (WiFi.encryptionType(i))
            {
            case WIFI_AUTH_OPEN:
                Serial.print("open");
                break;
            case WIFI_AUTH_WEP:
                Serial.print("WEP");
                break;
            case WIFI_AUTH_WPA_PSK:
                Serial.print("WPA");
                break;
            case WIFI_AUTH_WPA2_PSK:
                Serial.print("WPA2");
                break;
            case WIFI_AUTH_WPA_WPA2_PSK:
                Serial.print("WPA+WPA2");
                break;
            case WIFI_AUTH_WPA2_ENTERPRISE:
                Serial.print("WPA2-EAP");
                break;
            case WIFI_AUTH_WPA3_PSK:
                Serial.print("WPA3");
                break;
            case WIFI_AUTH_WPA2_WPA3_PSK:
                Serial.print("WPA2+WPA3");
                break;
            case WIFI_AUTH_WAPI_PSK:
                Serial.print("WAPI");
                break;
            default:
                Serial.print("unknown");
            }
            Serial.println();
            delay(10);
        }
    }
    }
  }

