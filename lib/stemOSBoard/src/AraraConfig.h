#ifndef AraraConfig_h
#define AraraConfig_h

struct {
    const int PORTA_1[2] = {4, 13};
    const int PORTA_2[2] = {18, 19};
    const int PORTA_3[2] = {23, 25};
    const int PORTA_4[2] = {32, 33};
    
} Motor;

struct {
    const int PORTA_1 = 2;
    const int PORTA_2 = 26;
    const int PORTA_3 = 27;
} Servo;

struct {
int PORTAS_TOTAIS[11] = {Motor.PORTA_1[0], Motor.PORTA_1[1],
                      Motor.PORTA_2[0], Motor.PORTA_2[1],
                      Motor.PORTA_3[0], Motor.PORTA_3[1],
                      Motor.PORTA_4[0], Motor.PORTA_4[1],
                      Servo.PORTA_1, Servo.PORTA_2, 
                      Servo.PORTA_3};

int QuantPortas = sizeof(PORTAS_TOTAIS) / sizeof(int);
} Portas;


#endif