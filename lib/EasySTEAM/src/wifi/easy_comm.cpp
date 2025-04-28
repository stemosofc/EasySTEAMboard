#include "easy_comm.hpp"
#include "wifi.hpp"

EasyWiFi wifi;

void stemWiFi::start() {
  LED::init();
  LED::CONFIGURE_WIFI();
  
  wifi.initAcessPoint();

  websocket.initWebServer();

  LED::NO_DS();
}