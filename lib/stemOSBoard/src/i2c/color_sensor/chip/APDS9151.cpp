#include "APDS9151.h"


i2c_port_num_t i2c_auto_port = -1;
gpio_num_t i2c_sda_port = GPIO_NUM_21;
gpio_num_t i2c_scl_port = GPIO_NUM_22;
uint32_t i2c_speed = 100000;
uint32_t timeout = 1000 / portTICK_PERIOD_MS;

i2c_master_bus_handle_t i2c__master_bus_handle;

i2c_master_bus_config_t i2c_master_bus_configure = {
    .i2c_port = i2c_auto_port,
    .sda_io_num = i2c_sda_port,
    .scl_io_num = i2c_scl_port,
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .glitch_ignore_cnt = 7,
    .intr_priority = 0,
};

i2c_device_config_t apds9151_i2c_configure = {
    .dev_addr_length = I2C_ADDR_BIT_LEN_7,
    .device_address = DEVICE::__DEVICE_ADDR,
    .scl_speed_hz = i2c_speed,
};

i2c_master_dev_handle_t apds9151_dev_handle;


void initialize()
{
    ESP_ERROR_CHECK_WITHOUT_ABORT(i2c_new_master_bus(&i2c_master_bus_configure, &i2c__master_bus_handle));
    ESP_ERROR_CHECK_WITHOUT_ABORT(i2c_master_bus_add_device(i2c__master_bus_handle, &apds9151_i2c_configure, &apds9151_dev_handle));
}

esp_err_t write_register(uint8_t reg, uint8_t data)
{
    uint8_t buff[2] = {reg, data};
    return i2c_master_transmit(apds9151_dev_handle, buff, sizeof(buff), timeout);
}

esp_err_t read_register(uint8_t reg, uint8_t len, uint8_t *data)
{
    return i2c_master_transmit_receive(apds9151_dev_handle, &reg, sizeof(reg), data, len, timeout);
}

esp_err_t device_is_conected()
{
    return i2c_master_probe(i2c__master_bus_handle, DEVICE::__DEVICE_ADDR, timeout);
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
    uint8_t psLed = ledPulseFreq | ledCurrent;
    ESP_ERROR_CHECK_WITHOUT_ABORT(write_register(REGISTERS::__PS_LED_ADDR, psLed));
}

void setPsPulsesConfigure(PS_PULSES numberOfLedPulses)
{
    ESP_ERROR_CHECK_WITHOUT_ABORT(write_register(REGISTERS::__PS_PULSES_ADDR, numberOfLedPulses));
}

void setPsMeasRateConfigure(PS_RESOLUTION psResolution, PS_MEASUREMENT_RATE psMeasurementRate)
{
    uint8_t psMeasRate = psResolution | psMeasurementRate;
    ESP_ERROR_CHECK_WITHOUT_ABORT(write_register(REGISTERS::__PS_MEAS_RATE_ADDR, psMeasRate));
}

void setLsMeasRateConfigure(LS_RESOLUTION lsResolution, LS_MEASUREMENT_RATE lsMeasurementRate)
{
    uint8_t lsMeasRate = lsResolution | lsMeasurementRate;
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