#include "stemOSboard.h"
#include "Arduino.h"

stemWiFi wifi;

void setup() {
  Serial.begin(115200);
  wifi.configureWiFiAP();
}

void loop() {
    Serial.println("Test");
}

