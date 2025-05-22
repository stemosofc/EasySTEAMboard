#include "Websockets.hpp"

bool DS_ENABLE = false;
bool ACTUATORS_ENABLE = false;

void Websocket::initWebServer() {
    server = new AsyncWebServer(80);
    ws = new AsyncWebSocket("/ws");
    ws->onEvent(std::bind(&Websocket::onEvent, this
        , std::placeholders::_1
        , std::placeholders::_2
        , std::placeholders::_3
        , std::placeholders::_4
        , std::placeholders::_5
        , std::placeholders::_6));
    server->addHandler(ws);
    server->begin();
}

JsonDocument Websocket::handleReceivedMessage(String message) {
    JsonDocument jon;                
    deserializeJson(jon, message); 
    DeserializationError err = deserializeJson(jon, message);
    errorJson(err);

    return jon;
}


void Websocket::errorJson(DeserializationError err) {
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

void Websocket::onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
 void *arg, uint8_t *data, size_t len) {
    switch (type) {
        case WS_EVT_CONNECT:
            id = client->id();
            client->text("Conectado");
            log_i("DS connected with id: %d\n", id);
            Gamepad::gamepad["EN"] = false;
            LED::OK();
        break;
        case WS_EVT_DISCONNECT:
            ACTUATORS_ENABLE = DS_ENABLE = false;
            Gamepad::reset();
            LED::NO_DS();
            log_i("DS disconnected");
        break;
        case WS_EVT_DATA:
        handleWebSocketMessage(arg, data, len);
        break;
        case WS_EVT_PONG:
        break;
        case WS_EVT_PING:
        break;
        case WS_EVT_ERROR:
        LED::ERRO();
        break;
    }
}

void Websocket::handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
    AwsFrameInfo *info = (AwsFrameInfo*)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
        JsonDocument jon;              
        DeserializationError err = deserializeJson(jon, data);
        errorJson(err);

        Gamepad::gamepad = jon;

        ACTUATORS_ENABLE = DS_ENABLE = Gamepad::status();

        bool comm = jon["COMM"] | true;
    } 
}

bool Websocket::hasClients()
{
    return ws->hasClient(id);
}

void Websocket::disconnectWebsocketClients(bool error) {
    Gamepad::reset();
    ws->closeAll();
    ws->cleanupClients(0);
    LED::ERRO();
    //log_e("Clients: %d", hasClients());
}