#include "EasySTEAM.h"

void setup() {
  Serial.begin(115200);
  easySTEAM.start();
}

void loop() {
  servo1.setPosition(0);
  delay(1000);
  servo1.setPosition(90);
  delay(1000);
  servo1.setPosition(270);
  delay(1000);
}

