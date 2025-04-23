#include "APDS9151.h"

const uint8_t ACK_ENABLED = 0;
const uint32_t i2c_speed = 100000;

i2c_device_config_t apds9151_i2c_configure = 
{
    .dev_addr_length = I2C_ADDR_BIT_LEN_7, 
    .device_address = __DEVICE_ADDR,
    .scl_speed_hz = i2c_speed,
    .flags = {.disable_ack_check = ACK_ENABLED}
};


i2c_master_dev_handle_t apds9151_dev_handle = NULL;

void initialize()
{
    esp_err_t bus_result = initialize_i2c_bus();
    if(bus_result) ESP_LOGE(TAG_COLOR, "I2C bus init failed with code: %s", esp_err_to_name(bus_result));

    esp_err_t device_result = initialize_i2c_device(&apds9151_i2c_configure, &apds9151_dev_handle);
    if(device_result) ESP_LOGE(TAG_COLOR, "Failed to add APDS-9151 to I2C bus, with code: %s", esp_err_to_name(device_result));
}

esp_err_t write_register(uint8_t reg, uint8_t data)
{
    uint8_t buff[2] = {reg, data};
    return i2c_write_data(&apds9151_dev_handle, buff, sizeof(buff));
}

esp_err_t read_register(uint8_t reg, uint8_t len, uint8_t *data)
{
    return i2c_read_data(&apds9151_dev_handle, &reg, sizeof(reg), data, len);
}

esp_err_t apds9151_is_connected()
{
    return i2c_device_is_connected(__DEVICE_ADDR);
}

uint8_t getMainCtrlConfigure()
{
    uint8_t main_ctrl = 0;
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(__MAIN_CTRL_ADDR, __1_BYTE, &main_ctrl));
    return main_ctrl;
}

uint8_t getPsLedConfigure()
{
    uint8_t psLed = 0;
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(__PS_LED_ADDR, __1_BYTE, &psLed));
    return psLed;
}

uint8_t getPsPulsesConfigure()
{
    uint8_t psPulses = 0;
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(__PS_PULSES_ADDR, __1_BYTE, &psPulses));
    return psPulses;
}

uint8_t getPsMeasRateConfigure()
{
    uint8_t psMeasRate = 0;
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(__PS_MEAS_RATE_ADDR, __1_BYTE, &psMeasRate));
    return psMeasRate;
}

uint8_t getLsMeasRateConfigure()
{
    uint8_t psMeasRate = 0;
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(__LS_MEAS_RATE_ADDR, __1_BYTE, &psMeasRate));
    return psMeasRate;
}

uint8_t getLsGainConfigure()
{
    uint8_t psMeasRate = 0;
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(__LS_GAIN_ADDR, __1_BYTE, &psMeasRate));
    return psMeasRate;
}

uint8_t getPartID()
{
    uint8_t partId = 0;
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(__PART_ID_ADDR, __1_BYTE, &partId));
    return partId;
}

uint8_t getMainStatus()
{
    uint8_t mainStatus = 0;
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(__MAIN_STATUS_ADDR, __1_BYTE, &mainStatus));
    return mainStatus;
}

uint8_t getInterruptConfigure()
{
    uint8_t intCfg = 0;
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(__INT_CFG_ADDR, __1_BYTE, &intCfg));
    return intCfg;
}

uint8_t getPersistInterruptConfigure()
{
    uint8_t intPst = 0;
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(__INT_PST_ADDR, __1_BYTE, &intPst));
    return intPst;
}

uint32_t getLsDataGreen()
{
    uint8_t data[3] = {0};
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(__LS_DATA_GREEN_0_ADDR, __3_BYTE, data));
    uint32_t greenColor = to_20_bit(data);
    return greenColor;
}

uint32_t getLsDataBlue()
{
    uint8_t data[3] = {0};
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(__LS_DATA_BLUE_0_ADDR, __3_BYTE, data));
    uint32_t blueColor = to_20_bit(data);
    return blueColor;
}

uint32_t getLsDataRed()
{
    uint8_t data[3] = {0};
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(__LS_DATA_RED_0_ADDR, __3_BYTE, data));
    uint32_t redColor = to_20_bit(data);
    return redColor;
}

uint32_t getLsDataIR()
{
    uint8_t data[3] = {0};
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(__LS_DATA_IR_0_ADDR, __3_BYTE, data));
    uint32_t ir = to_20_bit(data);
    return ir;
}

uint16_t getPsData()
{
    uint8_t data[2] = {0};
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(__PS_DATA_0_ADDR, __2_BYTE, data));
    uint32_t psData = to_11_bit(data);
    return psData;
}


void setMainCtrl(data_main_ctrl_t * data_main_ctrl, bool SAI_PS, bool SAI_LS, bool SW_RESET, bool RGB_MODE, bool LS_EN, bool PS_EN)
{
    data_main_ctrl->data_main_ctrl_u8 = getMainCtrlConfigure();
    data_main_ctrl->data_main_ctrl_bitmap.__SAI_PS = SAI_PS;
    data_main_ctrl->data_main_ctrl_bitmap.__SAI_LS = SAI_LS;
    data_main_ctrl->data_main_ctrl_bitmap.__SW_RESET = SW_RESET;
    data_main_ctrl->data_main_ctrl_bitmap.__RGB_MODE = RGB_MODE;
    data_main_ctrl->data_main_ctrl_bitmap.__LS_EN = LS_EN;
    data_main_ctrl->data_main_ctrl_bitmap.__PS_EN = PS_EN;

    ESP_ERROR_CHECK_WITHOUT_ABORT(write_register(__MAIN_CTRL_ADDR, data_main_ctrl->data_main_ctrl_u8));
}

void setPsLedConfigure(ps_led_t * ps_led)
{
    ESP_ERROR_CHECK_WITHOUT_ABORT(write_register(__PS_LED_ADDR, ps_led->ps_led_u8));
}

void setPsPulsesConfigure(ps_pulses_t * ps_pulses)
{
    ESP_ERROR_CHECK_WITHOUT_ABORT(write_register(__PS_PULSES_ADDR, ps_pulses->ps_pulses_u8));
}

void setPsMeasRateConfigure(ps_meas_rate_t * ps_meas)
{
    ESP_ERROR_CHECK_WITHOUT_ABORT(write_register(__PS_MEAS_RATE_ADDR, ps_meas->ps_meas_u8));
}

void setLsMeasRateConfigure(ls_meas_rate_t * ls_meas)
{
    ESP_ERROR_CHECK_WITHOUT_ABORT(write_register(__LS_MEAS_RATE_ADDR, ls_meas->ls_meas_u8));
}

void setLsGainConfigure(ls_gain_range_t * ls_gain)
{
    ESP_ERROR_CHECK_WITHOUT_ABORT(write_register(__LS_GAIN_ADDR, ls_gain->u8_ls_gain_range));
}

/*
void setInterruptionConfigure(INTERRUPT_CONFIGURE interruptionConfigure)
{
    ESP_ERROR_CHECK_WITHOUT_ABORT(write_register(__INT_CFG_ADDR, interruptionConfigure));
}

void setPersistInterruptionConfigure(INTERRUPT_PERSIST_CONFIGURE interruptionPersistConfigure)
{
    ESP_ERROR_CHECK_WITHOUT_ABORT(write_register(__INT_PST_ADDR, interruptionPersistConfigure));
}
*/

uint32_t to_20_bit(uint8_t data[3])
{
    return (((uint32_t)data[2] << 16) | ((uint16_t)(data[1] << 8)) | (data[0]));
}

uint16_t to_11_bit(uint8_t data[2])
{
    return (((uint16_t)data[1] << 8) | (data[0]));
}