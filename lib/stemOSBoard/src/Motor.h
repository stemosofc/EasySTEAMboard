#ifndef Motor_h
#define Motor_h
#include "Arduino.h"
#include "EncoderESP.h"

class Motor {
  public:
    Motor(int entrada, bool reverse); // Construtor da classe motor
    void setPower(double power); // Define a velocidade do motor (-1.0 a 1.0)
    EncoderESP encoderESP;
    static const int PORTA_1 = 1; // Portas de motor da placa
    static const int PORTA_2 = 2;
    static const int PORTA_3 = 3;
    static const int PORTA_4 = 4;
    static const bool REVERSE = true; // Direções do motor
    static const bool FORWARD = false;
  private:
    int pinPWMA; // Pino PWM A
    int pinPWMB; // Pino PWM B
    int channelA; // Canal PWM A
    int channelB; // Canal PWM B
    void pinos(int entrada); // Configura os pinos com base na porta do motor
    static const int RESOLUTION = 10; // Resolução (bits) do canal PWM (1024)
    static const int FREQUENCY = 20000; // Frequência do canal
};
#endif