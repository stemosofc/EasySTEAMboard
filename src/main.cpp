#include "EasySTEAM.h"
#include <Arduino.h>

void setup() {
  Serial.begin(115200);
<<<<<<< HEAD
  Serial.println("Iniciando");
  easySTEAM.start();
}
void loop() {

=======
}
void loop() {
  Serial.printf("Encoder pose: %lf\n", motor1.encoder.getPosition());
  Serial.printf("Encoder 2 pose: %lf\n", motor2.encoder.getPosition());
  delay(50);
>>>>>>> main
}