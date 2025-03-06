#include "EasySTEAM.h"
#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  easySTEAM.start();
  sensorColor.start();
  Serial.println("Teste");
  Serial.println("AAAAAAAAAA");
}

void loop() {
  Serial.printf("Blue: %d\n", sensorColor.getBlue());
  Serial.printf("Red: %d\n", sensorColor.getRed());
  Serial.printf("Green: %d\n", sensorColor.getGreen());
}