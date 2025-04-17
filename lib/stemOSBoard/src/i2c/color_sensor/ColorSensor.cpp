#include "ColorSensor.hpp"

#ifdef  __cplusplus
extern "C"
{
#endif    
    #include "chip/APDS9151.h"

    enum PS_CURRENT ps_current_100ma = __PULSE_CURRENT_100MA;
    enum PS_FREQUENCY ps_frequency_60hz = __FREQ_60K;

    enum PS_RESOLUTION ps_resolution_8bit = __PS_RESOLUTION_8bit;
    enum PS_MEASUREMENT_RATE ps_measurement_rate_100ms = __PS_MEASUREMENT_RATE_100ms;

    enum LS_RESOLUTION ls_resolution_18bits = __LS_RESOLUTION_18bit;
    enum LS_MEASUREMENT_RATE ls_measurement_rate_100ms = __LS_MEASUREMENT_RATE_100ms;

    enum GAIN ls_gain = __GAIN_3;

    data_main_ctrl_t main_ctrl = {.data_main_ctrl_u8 = __MAIN_CTRL_DEFAULT_VALUE};
    ps_led_t ps_led = {.ps_led_u8 = __PS_LED_DEFAULT_VALUE};
    ps_meas_rate_t ps_meas_rate = {.ps_meas_u8 = __PS_MEAS_RATE_DEFAULT_VALUE};
    ls_meas_rate_t ls_meas_rate = {.ls_meas_u8 = __LS_MEAS_RATE_DEFAULT_VALUE};
    ls_gain_range_t ls_gain_range = {.u8_ls_gain_range = __LS_GAIN_DEFAULT_VALUE};
#ifdef __cplusplus
}
#endif

// start color sensor
void ColorSensor::start()
{
    initialize();

    setMainCtrl(&main_ctrl, false, false, false, true, true, true);

    ps_led.ps_led_bitmap_t.__LED_CURRENT = ps_current_100ma;
    ps_led.ps_led_bitmap_t.__LED_PULSE_MODULATION_FREQUENCY = ps_frequency_60hz;

    setPsLedConfigure(&ps_led);

    ps_meas_rate.ps_meas_rate_bitmap.__PS_RESOLUTION = ps_resolution_8bit;
    ps_meas_rate.ps_meas_rate_bitmap.__PS_MEASUREMENT_RATE = ps_measurement_rate_100ms;

    setPsMeasRateConfigure(&ps_meas_rate);

    ls_meas_rate.ls_meas_rate_bitmap.__LS_MEASUREMENT_RATE =  ls_measurement_rate_100ms;
    ls_meas_rate.ls_meas_rate_bitmap.__LS_RESOLUTION = ls_resolution_18bits;

    setLsMeasRateConfigure(&ls_meas_rate);

    ls_gain_range.ls_gain_range_bitmap.__LS_GAIN_RANGE = ls_gain;

    setLsGainConfigure(&ls_gain_range);

    log_d("Main Ctrl: %d\n", getMainCtrlConfigure());
    log_d("Part ID: %d\n", getPartID());
}


int ColorSensor::getBlue()
{
    return getLsDataBlue();
}

int ColorSensor::getRed()
{
    return getLsDataRed();
}

int ColorSensor::getGreen()
{
    return getLsDataGreen();
}

int ColorSensor::getIR()
{
    return getLsDataIR();
}

int ColorSensor::getPS()
{
    return getPsData();
}