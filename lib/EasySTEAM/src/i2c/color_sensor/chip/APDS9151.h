#ifndef APDS9151_H
#define APDS9151_h


#include "i2c/i2c_driver.h"
#include "memory_address.h"
#include <stdbool.h>
static const char * TAG_COLOR = "ColorSensor";
extern i2c_device_config_t apds9151_i2c_configure;
extern i2c_master_dev_handle_t apds9151_dev_handle;

void initialize(); //

esp_err_t write_register(uint8_t reg, uint8_t data); //
esp_err_t read_register(uint8_t reg, uint8_t len, uint8_t *data); //
uint32_t to_20_bit(uint8_t data[3]); //
uint16_t to_11_bit(uint8_t data[2]); //

esp_err_t apds9151_is_connected(void);

uint8_t getMainCtrlConfigure(void); //
uint8_t getPsLedConfigure(void); //
uint8_t getPsPulsesConfigure(void); //
uint8_t getPsMeasRateConfigure(void); // 
uint8_t getLsMeasRateConfigure(void); //
uint8_t getLsGainConfigure(void); //
uint8_t getPartID(void); //
uint8_t getMainStatus(void); // 

uint8_t getInterruptConfigure(void); //
uint8_t getPersistInterruptConfigure(void); // 
uint16_t getPsThresholdUpConfigure(void);
uint16_t getPsThresholdLowConfigure(void);
uint16_t getLsThresholdUpConfigure(void);
uint16_t getLsThresholdLowConfigure(void);
uint16_t getLsThresholdVarianceConfigure(void);
//uint16_t getPsCAN(void);

uint32_t getLsDataGreen(void); // 
uint32_t getLsDataBlue(void); //
uint32_t getLsDataRed(void); //
uint32_t getLsDataIR(void); //
uint16_t getPsData(void); //

void setMainCtrl(data_main_ctrl_t * data_main_ctrl, bool SAI_PS, bool SAI_LS, bool SW_RESET, bool RGB_MODE, bool LS_EN, bool PS_EN); // 
void setPsLedConfigure(ps_led_t * ps_led); //
void setPsPulsesConfigure(ps_pulses_t * ps_pulses); //
void setPsMeasRateConfigure(ps_meas_rate_t * ps_meas_rate); //
void setLsMeasRateConfigure(ls_meas_rate_t * ls_meas_rate); //
void setLsGainConfigure(ls_gain_range_t * gain); //
/*
//void setInterruptionConfigure(INTERRUPT_CONFIGURE interruptionConfigure); // 
//void setPersistInterruptionConfigure(INTERRUPT_PERSIST_CONFIGURE interruptionPersistConfigure); //
void setPsThresholdUpValue();
void setPsThresholdLowValue();
void setPsCANValue();
void setLsThresholdLowValue();
void setLsThresholdUpValue();
void setLsThresholdVarianceValue();
*/

#endif