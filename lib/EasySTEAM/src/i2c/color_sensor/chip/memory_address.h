#ifndef memory_address
#define memory_address

#include <inttypes.h>

#define __DEVICE_ADDR 0x52

typedef uint8_t u8;

#define __MAIN_CTRL_ADDR 0x00
#define __PS_LED_ADDR 0x01
#define __PS_PULSES_ADDR 0x02
#define __PS_MEAS_RATE_ADDR 0x03
#define __LS_MEAS_RATE_ADDR 0x04
#define __LS_GAIN_ADDR 0x05
#define __PART_ID_ADDR 0x06
#define __MAIN_STATUS_ADDR 0x07
#define __PS_DATA_0_ADDR 0x08
#define __PS_DATA_1_ADDR 0x09
#define __LS_DATA_IR_0_ADDR 0x0A
#define __LS_DATA_IR_1_ADDR 0x0B
#define __LS_DATA_IR_2_ADDR 0x0C
#define __LS_DATA_GREEN_0_ADDR 0x0D
#define __LS_DATA_GREEN_1_ADDR 0x0E
#define __LS_DATA_GREEN_2_ADDR 0x0F
#define __LS_DATA_BLUE_0_ADDR 0x10
#define __LS_DATA_BLUE_1_ADDR 0x11
#define __LS_DATA_BLUE_2_ADDR 0x12
#define __LS_DATA_RED_0_ADDR 0x13
#define __LS_DATA_RED_1_ADDR 0x14
#define __LS_DATA_RED_2_ADDR 0x15
#define __INT_CFG_ADDR 0x19
#define __INT_PST_ADDR 0x1A
#define __PS_THRES_UP_0_ADDR 0x1B
#define __PS_THRES_UP_1_ADDR 0x1C
#define __PS_THRES_LOW_0_ADDR 0x1D
#define __PS_THRES_LOW_1_ADDR 0x1E
#define __PS_CAN_0_ADDR 0x1F
#define __PS_CAN_1_ADDR 0x20
#define __LS_THRES_UP_0_ADDR 0x21
#define __LS_THRES_UP_1_ADDR 0x22
#define __LS_THRES_UP_2_ADDR 0x23
#define __LS_THRES_LOW_0_ADDR 0x24
#define __LS_THRES_LOW_1_ADDR 0x25
#define __LS_THRES_LOW_2_ADDR 0x26
#define __LS_THRES_VAR_ADDR 0x27

#define __MAIN_CTRL_DEFAULT_VALUE 0x00
#define __PS_LED_DEFAULT_VALUE 0x36
#define __PS_PULSES_DEFAULT_VALUE 0x08
#define __PS_MEAS_RATE_DEFAULT_VALUE 0x05
#define __LS_MEAS_RATE_DEFAULT_VALUE 0x22
#define __LS_GAIN_DEFAULT_VALUE 0x01

typedef union
{
    struct data_main_ctrl_bitmap_t
    {
        u8 __PS_EN : 1;
        u8 __LS_EN : 1;
        u8 __RGB_MODE : 1;
        u8 __SW_RESET : 1;
        u8 __SAI_LS : 1;
        u8 __SAI_PS : 1;
        u8 : 1;
    } data_main_ctrl_bitmap;
    u8 data_main_ctrl_u8;
} data_main_ctrl_t;


enum PS_FREQUENCY {
    __FREQ_60K = 0x03,
    __FREQ_70K = 0x04,
    __FREQ_80K = 0x05,
    __FREQ_90K = 0x06,
    __FREQ_100K = 0x07,
};

enum PS_CURRENT {
    __PULSE_CURRENT_2_5MA = 0x00,
    __PULSE_CURRENT_5MA = 0x01,
    __PULSE_CURRENT_10MA = 0x02,
    __PULSE_CURRENT_25MA = 0x03,
    __PULSE_CURRENT_50MA = 0x04,
    __PULSE_CURRENT_75MA = 0x05,
    __PULSE_CURRENT_100MA = 0x06,
    __PULSE_CURRENT_125MA = 0x07,
};

typedef union 
{
    struct ps_led_bitmap
    {
        u8 __LED_CURRENT : 3;
        u8 : 1;
        u8 __LED_PULSE_MODULATION_FREQUENCY : 3;
        u8 : 1;
    } ps_led_bitmap_t;
    u8 ps_led_u8;
} ps_led_t;

enum PS_PULSES {
    __PS_PULSES_0 = 0b00000000,
    __PS_PULSES_8 = 0b00001000,
    __PS_PULSES_32 = 0b00100000,
    __PS_PULSES_255 = 0b11111111,
};

typedef union 
{
    struct ps_pulses_bitmap_t
    {
        u8 __PS_PULSES : 8;
    } ps_pulses_bitmap;
    u8 ps_pulses_u8;
} ps_pulses_t;

enum PS_RESOLUTION {
    __PS_RESOLUTION_8bit = 0,
    __PS_RESOLUTION_9bit = 1,
    __PS_RESOLUTION_10bit = 2,
    __PS_RESOLUTION_11bit = 3,
};

enum PS_MEASUREMENT_RATE {
    __PS_MEASUREMENT_RATE_6_25ms = 1,    
    __PS_MEASUREMENT_RATE_12_5ms = 2,
    __PS_MEASUREMENT_RATE_25ms = 3,
    __PS_MEASUREMENT_RATE_50ms = 4,
    __PS_MEASUREMENT_RATE_100ms = 5,
    __PS_MEASUREMENT_RATE_200ms = 6,
    __PS_MEASUREMENT_RATE_400ms = 7,
};

typedef union
{
    struct ps_meas_rate_bitmap_t
    {
        u8 __PS_MEASUREMENT_RATE : 3;
        u8 __PS_RESOLUTION : 2;
        u8 : 3;
    } ps_meas_rate_bitmap;
    u8 ps_meas_u8;
} ps_meas_rate_t;

enum LS_RESOLUTION {
    __LS_RESOLUTION_20bit = 0x00,
    __LS_RESOLUTION_19bit = 0x10,
    __LS_RESOLUTION_18bit = 0x20,  // default
    __LS_RESOLUTION_17bit = 0x30,
    __LS_RESOLUTION_16bit = 0x40,
    __LS_RESOLUTION_13bit = 0x50,
};

enum LS_MEASUREMENT_RATE {
    __LS_MEASUREMENT_RATE_25ms = 0x00,
    __LS_MEASUREMENT_RATE_50ms = 0x01,
    __LS_MEASUREMENT_RATE_100ms = 0x02, // default
    __LS_MEASUREMENT_RATE_200ms = 0x03,
    __LS_MEASUREMENT_RATE_500ms = 0x04,
    __LS_MEASUREMENT_RATE_1000ms = 0x05,
    __LS_MEASUREMENT_RATE_2000ms_0 = 0x06,
    __LS_MEASUREMENT_RATE_2000ms_1 = 0x07,
};

typedef union
{
    struct ls_meas_rate_bitmap_t
    {
        u8 __LS_MEASUREMENT_RATE : 3;
        u8 : 1;
        u8 __LS_RESOLUTION : 3;
        u8 : 1;
    } ls_meas_rate_bitmap;
    u8 ls_meas_u8;
} ls_meas_rate_t;

enum GAIN {
    __GAIN_1 = 0x00,
    __GAIN_3 = 0x01, // default
    __GAIN_6 = 0x02,
    __GAIN_9 = 0x03,
    __GAIN_18 = 0x04,
};

typedef union
{
    struct ls_gain_range_bitmap_t
    {
        u8 __LS_GAIN_RANGE : 3;
    } ls_gain_range_bitmap;
    u8 u8_ls_gain_range;
} ls_gain_range_t;



enum INTERRUPT_CONFIGURE {
    __PS_INT_EN = 0x01,
    __PS_LOGIC_MODE = 0x02,
    __LS_INT_EN = 0x04,
    __LS_VAR_MODE = 0x08,
    __LS_INT_SEL_IR_CHANNEL = 0x00,
    __LS_INT_SEL_ALS_CHANNEL = 0x10,
    __LS_INT_SEL_GEEN_CHANNEL = 0x20,
    __LS_INT_SEL_RED_CHANNEL = 0x30,
};

enum INTERRUPT_PERSIST_CONFIGURE {
    __LS_EVERY_VALUE = 0x01,
    __LS_2_VALUE = 0x02,
    __LS_3_VALUE = 0x02,
    __LS_4_VALUE = 0x03,
    __LS_35_VALUE = 0x04,
};


#define __1_BYTE 1
#define __2_BYTE 2
#define __3_BYTE 3

#endif