#ifndef MOTOR_H
#define MOTOR_H

#include "master.h"

class Motor {
  public:
    explicit Motor(int entrada, bool reverse=false); // Construtor da classe motor
    void setPower(double power); // Define a velocidade do motor (-1.0 a 1.0)
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
    static const int RESOLUTION = LEDC_TIMER_10_BIT; // Resolução (bits) do canal PWM (1024)
    static const int FREQUENCY = 10000; // Frequência do canal
    static const int MAX_OUTPUT = 972;
};
#endif