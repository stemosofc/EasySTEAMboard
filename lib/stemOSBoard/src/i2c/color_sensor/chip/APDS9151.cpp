#include "APDS9151.hpp"


const uint8_t ACK_ENABLED = 0;
const uint32_t i2c_speed = 100000;

i2c_device_config_t apds9151_i2c_configure = 
{.dev_addr_length = I2C_ADDR_BIT_LEN_7, 
.device_address = DEVICE::__DEVICE_ADDR,
.scl_speed_hz = i2c_speed,
.flags = {.disable_ack_check = ACK_ENABLED}
};


i2c_master_dev_handle_t apds9151_dev_handle = NULL;


void initialize()
{
    esp_err_t bus_result = initialize_i2c_bus();
    if(bus_result) log_e("I2C bus init failed with code: %s", esp_err_to_name(bus_result));

    esp_err_t device_result = initialize_i2c_device(&apds9151_i2c_configure, &apds9151_dev_handle);
    if(device_result) log_e("Failed to add APDS-9151 to I2C bus, with code: %s", esp_err_to_name(device_result));
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
    return i2c_device_is_connected(DEVICE::__DEVICE_ADDR);
}

uint8_t getMainCtrlConfigure()
{
    uint8_t main_ctrl;
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(REGISTERS::__MAIN_CTRL_ADDR, BUFFER_SIZES::__1_BYTE, &main_ctrl));
    return main_ctrl;
}

uint8_t getPsLedConfigure()
{
    uint8_t psLed;
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(REGISTERS::__PS_LED_ADDR, BUFFER_SIZES::__1_BYTE, &psLed));
    return psLed;
}

uint8_t getPsPulsesConfigure()
{
    uint8_t psPulses;
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(REGISTERS::__PS_PULSES_ADDR, BUFFER_SIZES::__1_BYTE, &psPulses));
    return psPulses;
}

uint8_t getPsMeasRateConfigure()
{
    uint8_t psMeasRate;
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(REGISTERS::__PS_MEAS_RATE_ADDR, BUFFER_SIZES::__1_BYTE, &psMeasRate));
    return psMeasRate;
}

uint8_t getLsMeasRateConfigure()
{
    uint8_t psMeasRate;
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(REGISTERS::__LS_MEAS_RATE_ADDR, BUFFER_SIZES::__1_BYTE, &psMeasRate));
    return psMeasRate;
}

uint8_t getLsGainConfigure()
{
    uint8_t psMeasRate;
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(REGISTERS::__LS_GAIN_ADDR, BUFFER_SIZES::__1_BYTE, &psMeasRate));
    return psMeasRate;
}

uint8_t getPartID()
{
    uint8_t partId;
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(REGISTERS::__PART_ID_ADDR, BUFFER_SIZES::__1_BYTE, &partId));
    return partId;
}

uint8_t getMainStatus()
{
    uint8_t mainStatus;
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(REGISTERS::__MAIN_STATUS_ADDR, BUFFER_SIZES::__1_BYTE, &mainStatus));
    return mainStatus;
}

uint8_t getInterruptConfigure()
{
    uint8_t intCfg;
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(REGISTERS::__INT_CFG_ADDR, BUFFER_SIZES::__1_BYTE, &intCfg));
    return intCfg;
}

uint8_t getPersistInterruptConfigure()
{
    uint8_t intPst;
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(REGISTERS::__INT_PST_ADDR, BUFFER_SIZES::__1_BYTE, &intPst));
    return intPst;
}

uint32_t getLsDataGreen()
{
    uint8_t data[3];
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(REGISTERS::__LS_DATA_GREEN_0_ADDR, BUFFER_SIZES::__3_BYTE, data));
    uint32_t greenColor = to_20_bit(data);
    return greenColor;
}

uint32_t getLsDataBlue()
{
    uint8_t data[3];
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(REGISTERS::__LS_DATA_BLUE_0_ADDR, BUFFER_SIZES::__3_BYTE, data));
    uint32_t blueColor = to_20_bit(data);
    return blueColor;
}

uint32_t getLsDataRed()
{
    uint8_t data[3];
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(REGISTERS::__LS_DATA_RED_0_ADDR, BUFFER_SIZES::__3_BYTE, data));
    uint32_t redColor = to_20_bit(data);
    return redColor;
}

uint32_t getLsDataIR()
{
    uint8_t data[3];
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(REGISTERS::__LS_DATA_IR_0_ADDR, BUFFER_SIZES::__3_BYTE, data));
    uint32_t ir = to_20_bit(data);
    return ir;
}

uint16_t getPsData()
{
    uint8_t data[2];
    ESP_ERROR_CHECK_WITHOUT_ABORT(read_register(REGISTERS::__PS_DATA_0_ADDR, BUFFER_SIZES::__2_BYTE, data));
    uint32_t psData = to_11_bit(data);
    return psData;
}


void setMainCtrl(bool SAI_PS, bool SAI_LS, bool SW_RESET, bool RGB_MODE, bool LS_EN, bool PS_EN)
{
    uint8_t main_ctrl = 0;
    if (SAI_PS)
    {
        main_ctrl |= DATA_MAIN_CTRL::__SAI_PS;
    }
    if (SAI_LS)
    {
        main_ctrl |= DATA_MAIN_CTRL::__SAI_LS;
    }
    if (SW_RESET)
    {
        main_ctrl |= DATA_MAIN_CTRL::__SW_RESET;
    }
    if (RGB_MODE)
    {
        main_ctrl |= DATA_MAIN_CTRL::__RGB_MODE;
    }
    if (LS_EN)
    {
        main_ctrl |= DATA_MAIN_CTRL::__LS_EN;
    }
    if (PS_EN)
    {
        main_ctrl |= DATA_MAIN_CTRL::__PS_EN;
    }
    ESP_ERROR_CHECK_WITHOUT_ABORT(write_register(REGISTERS::__MAIN_CTRL_ADDR, main_ctrl));
}

void setPsLedConfigure(PS_FREQUENCY ledPulseFreq, PS_CURRENT ledCurrent)
{
    uint8_t psLed = ((uint8_t)ledPulseFreq) | ((uint8_t)ledCurrent);
    ESP_ERROR_CHECK_WITHOUT_ABORT(write_register(REGISTERS::__PS_LED_ADDR, psLed));
}

void setPsPulsesConfigure(PS_PULSES numberOfLedPulses)
{
    ESP_ERROR_CHECK_WITHOUT_ABORT(write_register(REGISTERS::__PS_PULSES_ADDR, numberOfLedPulses));
}

void setPsMeasRateConfigure(PS_RESOLUTION psResolution, PS_MEASUREMENT_RATE psMeasurementRate)
{
    uint8_t psMeasRate = ((uint8_t)psResolution) | ((uint8_t)psMeasurementRate);
    ESP_ERROR_CHECK_WITHOUT_ABORT(write_register(REGISTERS::__PS_MEAS_RATE_ADDR, psMeasRate));
}

void setLsMeasRateConfigure(LS_RESOLUTION lsResolution, LS_MEASUREMENT_RATE lsMeasurementRate)
{
    uint8_t lsMeasRate = ((uint8_t)lsResolution) | ((uint8_t)lsMeasurementRate);
    ESP_ERROR_CHECK_WITHOUT_ABORT(write_register(REGISTERS::__LS_MEAS_RATE_ADDR, lsMeasRate));
}

void setLsGainConfigure(GAIN gain)
{
    ESP_ERROR_CHECK_WITHOUT_ABORT(write_register(REGISTERS::__LS_GAIN_ADDR, gain));
}

void setInterruptionConfigure(INTERRUPT_CONFIGURE interruptionConfigure)
{
    ESP_ERROR_CHECK_WITHOUT_ABORT(write_register(REGISTERS::__INT_CFG_ADDR, interruptionConfigure));
}

void setPersistInterruptionConfigure(INTERRUPT_PERSIST_CONFIGURE interruptionPersistConfigure)
{
    ESP_ERROR_CHECK_WITHOUT_ABORT(write_register(REGISTERS::__INT_PST_ADDR, interruptionPersistConfigure));
}


uint32_t to_20_bit(uint8_t data[3])
{
    return (((uint32_t)data[2] << 16) | ((uint16_t)(data[1] << 8)) | (data[0]));
}

uint16_t to_11_bit(uint8_t data[2])
{
    return (((uint16_t)data[1] << 8) | (data[0]));
}