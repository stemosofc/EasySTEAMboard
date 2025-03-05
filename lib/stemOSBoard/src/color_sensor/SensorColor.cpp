#include "SensorColor.h"

void SensorColor::start()
{
    initialize();

    setMainCtrl(false, false, false, true, true, true);
    setPsLedConfigure(PS_FREQUENCY::__FREQ_60K, PS_CURRENT::__PULSE_CURRENT_100MA);
    setPsMeasRateConfigure(PS_RESOLUTION::__PS_RESOLUTION_8bit, PS_MEASUREMENT_RATE::__PS_MEASUREMENT_RATE_100ms);
    setLsMeasRateConfigure(LS_RESOLUTION::__LS_RESOLUTION_18bit, LS_MEASUREMENT_RATE::__LS_MEASUREMENT_RATE_100ms);
    setLsGainConfigure(GAIN::__GAIN_3);
  
    log_d("Main Ctrl: %d\n", getMainCtrlConfigure());
    log_d("Part ID: %d\n", getPartID());
}


int SensorColor::getBlue()
{
    return getLsDataBlue();
}

int SensorColor::getRed()
{
    return getLsDataRed();
}

int SensorColor::getGreen()
{
    return getLsDataGreen();
}

int SensorColor::getIR()
{
    return getLsDataIR();
}

int SensorColor::getPS()
{
    return getPsData();
}