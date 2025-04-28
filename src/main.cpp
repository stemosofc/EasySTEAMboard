#include "EasySTEAM.h"

void setup() {
  Serial.begin(115200);
  easySTEAM.start();
<<<<<<< HEAD
=======
  colorSensor.start();
>>>>>>> main
}

boolean previousAstate = false;
boolean previousBstate = false;
boolean servo1Toggle = false;
boolean servo2Toggle = false;

void loop() {
<<<<<<< HEAD

=======
  double y = gamepad.getLeftAxisY();
  double  x = gamepad.getLeftAxisX();
  double armPower = gamepad.getRightAxisY();
  boolean buttonA =  gamepad.getButtonA();
  boolean buttonB = gamepad.getButtonB();

  if(!di1.getInput())
  {
    Serial.printf("Reseting encoder\n");
    encoder1.reset();
  }


  double powerLeft = y + x;
  double powerRight = y - x;

  motor1.setPower(-powerLeft);
  motor4.setPower(powerRight);
  motor3.setPower(-armPower);

  if(buttonA && !previousAstate)
  {
    servo1Toggle = !servo1Toggle;
  } 

  if(buttonB && !previousBstate)
  {
    servo2Toggle = !servo2Toggle;
  }

  if(servo1Toggle)
  {
    servo1.setPosition(270);
  }
  else
  {
    servo1.setPosition(0);
  }


  if(servo2Toggle)
  {
    servo2.setPosition(60);
  }
  else
  {
    servo2.setPosition(0);
  }

  Serial.printf("Red: %d\n", colorSensor.getRed());
  Serial.printf("Green: %d\n", colorSensor.getGreen());
  Serial.printf("Blue: %d\n", colorSensor.getBlue());
  Serial.printf("Encoder 1: %f\n", encoder1.getPosition());
  previousAstate = buttonA;
  previousBstate = buttonB;
>>>>>>> main
}