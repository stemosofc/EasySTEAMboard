#include "imu.hpp"

icm0948_config_i2c_t icm_config = {
	.i2c_port = I2C_NUM_0,
	.i2c_addr = ICM_20948_I2C_ADDR_AD1
};

icm20948_device_t icm;

bool IMU::alreadyCreated = false;

void IMU::start()
{
    if(alreadyCreated)
    {
        log_e("Don't possible to create a new IMU object!");
        return;
    }
    i2c_initialize(&icm20948_dev_cfg, &icm20948_dev_handle);

    icm20948_init_i2c(&icm, &icm_config);
    bool status_wia = false;

    do 
	{
        status_wia = icm20948_check_id(&icm) == ICM_20948_STAT_OK;
        if(status_wia)
        {
            break;
        }
		log_e("check ID failed");
		vTaskDelay(1000 / portTICK_PERIOD_MS);
    } while(!status_wia);

    icm20948_status_e stat = ICM_20948_STAT_ERR;
    uint8_t whoami = 0x00;

    do
    {
        stat = icm20948_get_who_am_i(&icm, &whoami);
        if((stat == ICM_20948_STAT_OK) || (whoami == ICM_20948_WHOAMI))
        {
            log_i("IMU connected with WIA: %d", whoami);
            break;
        }
        log_e("Error IMU with WIA: %d", whoami);
    } while ((stat != ICM_20948_STAT_OK) || (whoami != ICM_20948_WHOAMI));

    defaultStartup();
}

void IMU::defaultStartup()
{
    // icm in a know state
	icm20948_sw_reset(&icm);
	vTaskDelay(250 / portTICK_PERIOD_MS);

	icm20948_internal_sensor_id_bm sensors = (icm20948_internal_sensor_id_bm)(ICM_20948_INTERNAL_ACC | ICM_20948_INTERNAL_GYR);

	// Set Gyro and Accelerometer to a particular sample mode
	// optiona: SAMPLE_MODE_CONTINUOUS. SAMPLE_MODE_CYCLED
	icm20948_set_sample_mode(&icm, sensors, SAMPLE_MODE_CONTINUOUS); 

	// Set full scale ranges for both acc and gyr
	icm20948_fss_t myfss;
	myfss.a = GPM_2;   // (icm20948_accel_config_fs_sel_e)
	myfss.g = DPS_250; // (icm20948_gyro_config_1_fs_sel_e)
	icm20948_set_full_scale(&icm, sensors, myfss);

	// Set up DLPF configuration
	icm20948_dlpcfg_t myDLPcfg;
	myDLPcfg.a = ACC_D473BW_N499BW;
	myDLPcfg.g = GYR_D361BW4_N376BW5;
	icm20948_set_dlpf_cfg(&icm, sensors, myDLPcfg);

	// Choose whether or not to use DLPF
	icm20948_enable_dlpf(&icm, ICM_20948_INTERNAL_ACC, false);
	icm20948_enable_dlpf(&icm, ICM_20948_INTERNAL_GYR, false);

	// Now wake the sensor up
	icm20948_sleep(&icm, false);
	icm20948_low_power(&icm, false);

    init_dmp(&icm);
}

void IMU::init_dmp(icm20948_device_t *icm)
{
    bool success = true; // Use success to show if the DMP configuration was successful

    // Initialize the DMP with defaults.
    success &= (icm20948_init_dmp_sensor_with_defaults(icm) == ICM_20948_STAT_OK);
    // DMP sensor options are defined in ICM_20948_DMP.h
    //    INV_ICM20948_SENSOR_ACCELEROMETER               (16-bit accel)
    //    INV_ICM20948_SENSOR_GYROSCOPE                   (16-bit gyro + 32-bit calibrated gyro)
    //    INV_ICM20948_SENSOR_RAW_ACCELEROMETER           (16-bit accel)
    //    INV_ICM20948_SENSOR_RAW_GYROSCOPE               (16-bit gyro + 32-bit calibrated gyro)
    //    INV_ICM20948_SENSOR_MAGNETIC_FIELD_UNCALIBRATED (16-bit compass)
    //    INV_ICM20948_SENSOR_GYROSCOPE_UNCALIBRATED      (16-bit gyro)
    //    INV_ICM20948_SENSOR_STEP_DETECTOR               (Pedometer Step Detector)
    //    INV_ICM20948_SENSOR_STEP_COUNTER                (Pedometer Step Detector)
    //    INV_ICM20948_SENSOR_GAME_ROTATION_VECTOR        (32-bit 6-axis quaternion)
    //    INV_ICM20948_SENSOR_ROTATION_VECTOR             (32-bit 9-axis quaternion + heading accuracy)
    //    INV_ICM20948_SENSOR_GEOMAGNETIC_ROTATION_VECTOR (32-bit Geomag RV + heading accuracy)
    //    INV_ICM20948_SENSOR_GEOMAGNETIC_FIELD           (32-bit calibrated compass)
    //    INV_ICM20948_SENSOR_GRAVITY                     (32-bit 6-axis quaternion)
    //    INV_ICM20948_SENSOR_LINEAR_ACCELERATION         (16-bit accel + 32-bit 6-axis quaternion)
    //    INV_ICM20948_SENSOR_ORIENTATION                 (32-bit 9-axis quaternion + heading accuracy)

    // Enable the DMP orientation sensor
    success &= (inv_icm20948_enable_dmp_sensor(icm, INV_ICM20948_SENSOR_ORIENTATION, 1) == ICM_20948_STAT_OK);

    // Enable any additional sensors / features
    //success &= (myICM.enableDMPSensor(INV_ICM20948_SENSOR_RAW_GYROSCOPE) == ICM_20948_STAT_OK);
    //success &= (myICM.enableDMPSensor(INV_ICM20948_SENSOR_RAW_ACCELEROMETER) == ICM_20948_STAT_OK);
    //success &= (myICM.enableDMPSensor(INV_ICM20948_SENSOR_MAGNETIC_FIELD_UNCALIBRATED) == ICM_20948_STAT_OK);

    // Configuring DMP to output data at multiple ODRs:
    // DMP is capable of outputting multiple sensor data at different rates to FIFO.
    // Setting value can be calculated as follows:
    // Value = (DMP running rate / ODR ) - 1
    // E.g. For a 5Hz ODR rate when DMP is running at 55Hz, value = (55/5) - 1 = 10.
    success &= (inv_icm20948_set_dmp_sensor_period(icm, DMP_ODR_Reg_Quat9, 0) == ICM_20948_STAT_OK); // Set to the maximum
    //success &= (myICM.setDMPODRrate(DMP_ODR_Reg_Accel, 0) == ICM_20948_STAT_OK); // Set to the maximum
    //success &= (myICM.setDMPODRrate(DMP_ODR_Reg_Gyro, 0) == ICM_20948_STAT_OK); // Set to the maximum
    //success &= (myICM.setDMPODRrate(DMP_ODR_Reg_Gyro_Calibr, 0) == ICM_20948_STAT_OK); // Set to the maximum
    //success &= (myICM.setDMPODRrate(DMP_ODR_Reg_Cpass, 0) == ICM_20948_STAT_OK); // Set to the maximum
    //success &= (myICM.setDMPODRrate(DMP_ODR_Reg_Cpass_Calibr, 0) == ICM_20948_STAT_OK); // Set to the maximum

    success &= (icm20948_enable_fifo(icm, true) == ICM_20948_STAT_OK);

    success &= (icm20948_enable_dmp(icm, 1) == ICM_20948_STAT_OK);

    success &= (icm20948_reset_dmp(icm) == ICM_20948_STAT_OK);

    success &= (icm20948_reset_fifo(icm) == ICM_20948_STAT_OK);


    if (success)
    {
        log_i("DMP enabled");
    } else {
        log_e("Enable DMP failed!");
        while (1)
        ; // Do nothing more
    }

    alreadyCreated = true;
    
    setName("IMU");
    setPriority(1);
    setStackSize(2500);
    init(); // Init freeRTOS task
}

void IMU::calc()
{
    for(;;)
    {
        icm_20948_DMP_data_t data;
        icm20948_status_e status = inv_icm20948_read_dmp_data(&icm, &data);
            /* Was valid data available? */
        if ((status == ICM_20948_STAT_OK) || (status == ICM_20948_STAT_FIFO_MORE_DATA_AVAIL)) 
        {
            /* We have asked for orientation data so we should receive Quat9 */
            if ((data.header & DMP_header_bitmap_Quat9) > 0) 
            {
                // Q0 value is computed from this equation: Q0^2 + Q1^2 + Q2^2 + Q3^2 = 1.
                // In case of drift, the sum will not add to 1, therefore, quaternion data need to be corrected with right bias values.
                // The quaternion data is scaled by 2^30.
                // Scale to +/- 1
                double q1 = ((double)data.Quat9.Data.Q1) / 1073741824.0; // Convert to double. Divide by 2^30
                double q2 = ((double)data.Quat9.Data.Q2) / 1073741824.0; // Convert to double. Divide by 2^30
                double q3 = ((double)data.Quat9.Data.Q3) / 1073741824.0; // Convert to double. Divide by 2^30
                double q0 = sqrt(1.0 - ((q1 * q1) + (q2 * q2) + (q3 * q3)));
    
                qw = q0; // See issue #145 - thank you @Gord1
                qx = q2;
                qy = q1;
                qz = -q3;
                }
        }
        if(status != ICM_20948_STAT_FIFO_MORE_DATA_AVAIL) 
        {
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
    }
}

double IMU::getYaw()
{
    double t3 = +2.0 * (qw * qz + qx * qy);
    double t4 = +1.0 - 2.0 * (qy * qy + qz * qz);
    return atan2(t3, t4) * 180.0 / M_PI;
}

double IMU::getPitch()
{
    double t2 = +2.0 * (qw * qy - qx * qz);
    t2 = t2 > 1.0 ? 1.0 : t2;
    t2 = t2 < -1.0 ? -1.0 : t2;
    return asin(t2) * 180.0 / M_PI;
}

double IMU::getRoll()
{
    double t0 = +2.0 * (qw * qx + qy * qz);
    double t1 = +1.0 - 2.0 * (qx * qx + qy * qy);
    return atan2(t0, t1) * 180.0 / M_PI;
}