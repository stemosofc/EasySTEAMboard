#ifndef AraraConfig_h
#define AraraConfig_h

#define CONFIG_RESTART_DEBUG_INFO 1
// EN: Preserve debugging information across device software restarts
// RU: Сохранять отладочную информацию при программном перезапуске устройства
#define CONFIG_RESTART_DEBUG_INFO 1
// EN: Allow heap information to be saved periodically, with subsequent output on restart
// RU: Разрешить периодическое сохранение информации о куче / памяти с последующем выводом при перезапуске
#define CONFIG_RESTART_DEBUG_HEAP_SIZE_SCHEDULE 1
// EN: Depth to save the processor stack on restart. 0 - do not save
// RU: Глубина сохранения стека процессора при перезапуске. 0 - не сохранять
#define CONFIG_RESTART_DEBUG_STACK_DEPTH 28

#if CONFIG_RESTART_DEBUG_INFO
    typedef struct {
    size_t heap_total;
    size_t heap_free;
    size_t heap_free_min;
    time_t heap_min_time;
    #if CONFIG_RESTART_DEBUG_STACK_DEPTH > 0
    uint32_t backtrace[CONFIG_RESTART_DEBUG_STACK_DEPTH];
    #endif // CONFIG_RESTART_DEBUG_STACK_DEPTH
    } re_restart_debug_t;
#endif // CONFIG_RESTART_DEBUG_INFO


#if CONFIG_RESTART_DEBUG_INFO
__NOINIT_ATTR static re_restart_debug_t _debug_info;
#endif // CONFIG_RESTART_DEBUG_INFO

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

int PORTAS_TOTAIS[11] = {Motor.PORTA_1[0], Motor.PORTA_1[1],
                      Motor.PORTA_2[0], Motor.PORTA_2[1],
                      Motor.PORTA_3[0], Motor.PORTA_3[1],
                      Motor.PORTA_4[0], Motor.PORTA_4[1],
                      Servo.PORTA_1, Servo.PORTA_2, 
                      Servo.PORTA_3};

int QuantPortas = sizeof(PORTAS_TOTAIS) / sizeof(int);

#endif