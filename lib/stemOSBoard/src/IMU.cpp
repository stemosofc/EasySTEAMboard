#include "IMU.h"

/**
 * @brief Inicia o IMU
 *
 * @param [void]
 * @return N/A.
 */
void IMU::init() {
  Wire.begin();
  Wire.setClock(400000);

  myICM.enableDebugging(); // Uncomment this line to enable helpful debug messages on Serial

  bool initialized = false;

  while (!initialized)
  {
    myICM.begin(Wire, AD0_VAL);

    log_d("Initialization of the sensor returned", Serial.println(myICM.statusString()));

    if (myICM.status != ICM_20948_Stat_Ok)
    {

      log_d("Trying again...");

      delay(500);
    }
    else
    {
      initialized = true;
    }
  }

  log_i("IMU conectado!");


  bool success = true; // Use success to show if the DMP configuration was successful

  // Initialize the DMP. initializeDMP is a weak function. You can overwrite it if you want to e.g. to change the sample rate
  success &= (myICM.initializeDMP() == ICM_20948_Stat_Ok);

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

  success &= (myICM.enableDMPSensor(INV_ICM20948_SENSOR_GAME_ROTATION_VECTOR) == ICM_20948_Stat_Ok);

  // Configuring DMP to output data at multiple ODRs:
  // DMP is capable of outputting multiple sensor data at different rates to FIFO.
  // Setting value can be calculated as follows:
  // Value = (DMP running rate / ODR ) - 1
  // E.g. For a 5Hz ODR rate when DMP is running at 55Hz, value = (55/5) - 1 = 10.
  success &= (myICM.setDMPODRrate(DMP_ODR_Reg_Quat6, 0) == ICM_20948_Stat_Ok); // Set to the maximum

  // Enable the FIFO
  success &= (myICM.enableFIFO() == ICM_20948_Stat_Ok);

  // Enable the DMP
  success &= (myICM.enableDMP() == ICM_20948_Stat_Ok);

  // Reset DMP
  success &= (myICM.resetDMP() == ICM_20948_Stat_Ok);

  // Reset FIFO
  success &= (myICM.resetFIFO() == ICM_20948_Stat_Ok);

  // Check success
  if (success)
  {
    log_d("DMP enabled!");
  }
  else
  {
    log_e("DMP Não habilitado!");
  }
  setStackSize(2000);
  start();
}

/**
 * @brief Obtém os quaternions do IMU
 *
 * @param [void]
 * @return N/A.
 */
void IMU::calcule() {
  while(1) {
    // Read any DMP data waiting in the FIFO
    // Note:
    //    readDMPdataFromFIFO will return ICM_20948_Stat_FIFONoDataAvail if no data is available.
    //    If data is available, readDMPdataFromFIFO will attempt to read _one_ frame of DMP data.
    //    readDMPdataFromFIFO will return ICM_20948_Stat_FIFOIncompleteData if a frame was present but was incomplete
    //    readDMPdataFromFIFO will return ICM_20948_Stat_Ok if a valid frame was read.
    //    readDMPdataFromFIFO will return ICM_20948_Stat_FIFOMoreDataAvail if a valid frame was read _and_ the FIFO contains more (unread) data.
    icm_20948_DMP_data_t data;
    myICM.readDMPdataFromFIFO(&data);

    if ((myICM.status == ICM_20948_Stat_Ok) || (myICM.status == ICM_20948_Stat_FIFOMoreDataAvail)) // Was valid data available?
    {

      if ((data.header & DMP_header_bitmap_Quat6) > 0) // We have asked for GRV data so we should receive Quat6
      {
        q1 = ((double)data.Quat6.Data.Q1) / 1073741824.0; // Convert to double. Divide by 2^30
        q2 = ((double)data.Quat6.Data.Q2) / 1073741824.0; // Convert to double. Divide by 2^30
        q3 = ((double)data.Quat6.Data.Q3) / 1073741824.0; // Convert to double. Divide by 2^30

        // Convert the quaternions to Euler angles (roll, pitch, yaw)
        // https://en.wikipedia.org/w/index.php?title=Conversion_between_quaternions_and_Euler_angles&section=8#Source_code_2

        q0 = sqrt(1.0 - ((q1 * q1) + (q2 * q2) + (q3 * q3)));

        q2sqr = q2 * q2;
      }
    }

    if (myICM.status != ICM_20948_Stat_FIFOMoreDataAvail) // If more data is available then we should read it right away - and not delay
    {
      delay(10);
    }
  }
}

/**
 * @brief Retorna o valor do Roll (Eixo X) do IMU
 *
 * @param [void]
 * @return double.
 */
double IMU::getRoll() {
  // roll (x-axis rotation)
  double t0 = +2.0 * (q0 * q1 + q2 * q3);
  double t1 = +1.0 - 2.0 * (q1 * q1 + q2sqr);
  double roll = atan2(t0, t1) * 180.0 / PI;
  return roll;
}

/**
 * @brief Retorna o valor do Roll (Eixo Y) do IMU
 *
 * @param [void]
 * @return double.
 */
double IMU::getPitch() {
  // pitch (y-axis rotation)
  double t2 = +2.0 * (q0 * q2 - q3 * q1);
  t2 = t2 > 1.0 ? 1.0 : t2;
  t2 = t2 < -1.0 ? -1.0 : t2;
  double pitch = asin(t2) * 180.0 / PI;
  return pitch;
}

/**
 * @brief Retorna o valor do Roll (Eixo Z) do IMU
 *
 * @param [void]
 * @return double.
 */
double IMU::getYaw() {
  // yaw (z-axis rotation)
  double t3 = +2.0 * (q0 * q3 + q1 * q2);
  double t4 = +1.0 - 2.0 * (q2sqr + q3 * q3);
  double yaw = atan2(t3, t4) * 180.0 / PI;
  return yaw;
}