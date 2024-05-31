#ifndef AraraConfig_h
#define AraraConfig_h
#define FORMAT_LITTLEFS_IF_FAILED true
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

#if CONFIG_RESTART_DEBUG_INFO && (CONFIG_RESTART_DEBUG_STACK_DEPTH > 0)
#include "esp_types.h"
#include "esp_attr.h"
#include "esp_err.h"
#include "esp_debug_helpers.h"
#include "soc/soc_memory_layout.h"
#include "soc/cpu.h" 
#include "esp_system.h"
#endif // CONFIG_RESTART_STACK_DEPTH
#if CONFIG_RESTART_DEBUG_INFO
void IRAM_ATTR debugHeapUpdate()
{
  _debug_info.heap_total = heap_caps_get_total_size(MALLOC_CAP_DEFAULT);
  _debug_info.heap_free = heap_caps_get_free_size(MALLOC_CAP_DEFAULT);
  size_t _new_free_min = heap_caps_get_minimum_free_size(MALLOC_CAP_DEFAULT);
  if ((_debug_info.heap_free_min == 0) || (_new_free_min < _debug_info.heap_free_min)) {
    _debug_info.heap_free_min = _new_free_min;
    _debug_info.heap_min_time = time(nullptr);
  };
}
#if CONFIG_RESTART_DEBUG_STACK_DEPTH > 0
void IRAM_ATTR debugBacktraceUpdate()
{
  esp_backtrace_frame_t stk_frame;
  esp_backtrace_get_start(&(stk_frame.pc), &(stk_frame.sp), &(stk_frame.next_pc)); 
  _debug_info.backtrace[0] = esp_cpu_process_stack_pc(stk_frame.pc);
  bool corrupted = (esp_stack_ptr_is_sane(stk_frame.sp) &&
                    esp_ptr_executable((void*)esp_cpu_process_stack_pc(stk_frame.pc))) ?
                    false : true; 
  #if CONFIG_RESTART_DEBUG_STACK_DEPTH > 1
    uint8_t i = CONFIG_RESTART_DEBUG_STACK_DEPTH;
    while (i-- > 0 && stk_frame.next_pc != 0 && !corrupted) {
      if (!esp_backtrace_get_next_frame(&stk_frame)) {
        corrupted = true;
      };
      _debug_info.backtrace[CONFIG_RESTART_DEBUG_STACK_DEPTH - i] = esp_cpu_process_stack_pc(stk_frame.pc);
    };
  #endif // CONFIG_RESTART_DEBUG_STACK_DEPTH > 1
}
#endif // CONFIG_RESTART_DEBUG_STACK_DEPTH
void IRAM_ATTR debugUpdate()
{
  debugHeapUpdate();
  #if CONFIG_RESTART_DEBUG_STACK_DEPTH > 0
  debugBacktraceUpdate();
  #endif // CONFIG_RESTART_DEBUG_STACK_DEPTH
}
#endif

re_restart_debug_t debugGet ()
{
  re_restart_debug_t ret;
  memset ( &ret, 0, sizeof ( re_restart_debug_t )) ;
  esp_reset_reason_t esp_reason= esp_reset_reason () ;
  if (( esp_reason != ESP_RST_UNKNOWN ) && ( esp_reason != ESP_RST_POWERON )) {  
    ret = _debug_info;
    if ( _debug_info. heap_total > heap_caps_get_total_size ( MALLOC_CAP_DEFAULT )) {    
      memset ( &ret, 0, sizeof ( re_restart_debug_t )) ;
    } ;
  } ;
  memset ( &_debug_info, 0, sizeof ( re_restart_debug_t )) ;
  return ret;
}

#ifdef __cplusplus
extern "C"
{
#endif

void __real_esp_panic_handler(void*);
void __wrap_esp_panic_handler(void* info) 
{

  esp_rom_printf("Um erro ocorreu \n");
  debugBacktraceUpdate();
  // Call the original panic handler function to finish processing this error (creating a core dump for example...)
  __real_esp_panic_handler(info);
}

#ifdef __cplusplus
} // extern "C"
#endif

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