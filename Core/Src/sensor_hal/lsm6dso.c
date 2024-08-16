/*
 ******************************************************************************
 * @file    read_data_drdy.c
 * @author  Sensors Software Solution Team
 * @brief   This file shows how to get data from sensor.
 *
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/*
 * This example was developed using the following STMicroelectronics
 * evaluation boards:
 *
 * - STEVAL_MKI109V3 + STEVAL-MKI197V1
 * - NUCLEO_F401RE + STEVAL-MKI197V1
 * - DISCOVERY_SPC584B + STEVAL-MKI197V1
 *
 * Used interfaces:
 *
 * STEVAL_MKI109V3    - Host side:   USB (Virtual COM)
 *                    - Sensor side: SPI(Default) / I2C(supported)
 *
 * NUCLEO_STM32F401RE - Host side: UART(COM) to USB bridge
 *                    - Sensor side: I2C(Default) / SPI(supported)
 *
 * DISCOVERY_SPC584B  - Host side: UART(COM) to USB bridge
 *                    - Sensor side: I2C(Default) / SPI(supported)
 *
 * If you need to run this example on a different hardware platform a
 * modification of the functions: `platform_write`, `platform_read`,
 * `tx_com` and 'platform_init' is required.
 *
 */

/* STMicroelectronics evaluation boards definition
 *
 * Please uncomment ONLY the evaluation boards in use.
 * If a different hardware is used please comment all
 * following target board and redefine yours.
 */

//#define STEVAL_MKI109V3  /* little endian */
//#define NUCLEO_F401RE    /* little endian */
//#define SPC584B_DIS      /* big endian */

/* ATTENTION: By default the driver is little endian. If you need switch
 *            to big endian please see "Endianness definitions" in the
 *            header file of the driver (_reg.h).
 */

/* Includes ------------------------------------------------------------------*/
#include "sensor_hal/lsm6dso.h"

/* Private macro -------------------------------------------------------------*/
#define    BOOT_TIME            10 //ms

/* Private variables ---------------------------------------------------------*/
static int16_t data_raw_acceleration[3];
static int16_t data_raw_angular_rate[3];
static int16_t data_raw_temperature;
static float acceleration_mg[3];
static float angular_rate_mdps[3];
static float temperature_degC;
static uint8_t whoamI, rst;
static uint8_t tx_buffer[1000];

/* Extern variables ----------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/*
 *   WARNING:
 *   Functions declare in this section are defined at the end of this file
 *   and are strictly related to the hardware platform used.
 *
 */
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len);
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len);

static   stmdev_ctx_t dev_ctx;

void lsm6dsox_read_data_drdy_handler(void)
{
    uint8_t reg;

    /* Read output only if new xl value is available */
    lsm6dsox_xl_flag_data_ready_get(&dev_ctx, &reg);

    if (reg) {
      /* Read acceleration field data */
      memset(data_raw_acceleration, 0x00, 3 * sizeof(int16_t));
      lsm6dsox_acceleration_raw_get(&dev_ctx, data_raw_acceleration);
      acceleration_mg[0] =
        lsm6dsox_from_fs2_to_mg(data_raw_acceleration[0]);
      acceleration_mg[1] =
        lsm6dsox_from_fs2_to_mg(data_raw_acceleration[1]);
      acceleration_mg[2] =
        lsm6dsox_from_fs2_to_mg(data_raw_acceleration[2]);
      sprintf((char *)tx_buffer,
              "Acceleration [mg]:%4.2f\t%4.2f\t%4.2f\r\n",
              acceleration_mg[0], acceleration_mg[1], acceleration_mg[2]);
      print_console(tx_buffer);
    }

    lsm6dsox_gy_flag_data_ready_get(&dev_ctx, &reg);

    if (reg) {
      /* Read angular rate field data */
      memset(data_raw_angular_rate, 0x00, 3 * sizeof(int16_t));
      lsm6dsox_angular_rate_raw_get(&dev_ctx, data_raw_angular_rate);
      angular_rate_mdps[0] =
        lsm6dsox_from_fs2000_to_mdps(data_raw_angular_rate[0]);
      angular_rate_mdps[1] =
        lsm6dsox_from_fs2000_to_mdps(data_raw_angular_rate[1]);
      angular_rate_mdps[2] =
        lsm6dsox_from_fs2000_to_mdps(data_raw_angular_rate[2]);
      sprintf((char *)tx_buffer,
              "Angular rate [mdps]:%4.2f\t%4.2f\t%4.2f\r\n",
              angular_rate_mdps[0], angular_rate_mdps[1], angular_rate_mdps[2]);
      print_console(tx_buffer);
    }

    lsm6dsox_temp_flag_data_ready_get(&dev_ctx, &reg);

    if (reg) {
      /* Read temperature data */
      memset(&data_raw_temperature, 0x00, sizeof(int16_t));
      lsm6dsox_temperature_raw_get(&dev_ctx, &data_raw_temperature);
      temperature_degC = lsm6dsox_from_lsb_to_celsius(
                           data_raw_temperature);
      sprintf((char *)tx_buffer,
              "Temperature [degC]:%6.2f\r\n", temperature_degC);
      print_console(tx_buffer);
    }
}

/* Main Example --------------------------------------------------------------*/
void lsm6dsox_read_data_drdy_init(void)
{
  lsm6dsox_pin_int2_route_t int2_route;

  /* Initialize mems driver interface */
  dev_ctx.write_reg = platform_write;
  dev_ctx.read_reg = platform_read;
  dev_ctx.handle = &hspi2;
  /* Check device ID */
  lsm6dsox_device_id_get(&dev_ctx, &whoamI);

  if (whoamI != LSM6DSOX_ID)
    while (1);

  /* Restore default configuration */
  lsm6dsox_reset_set(&dev_ctx, PROPERTY_ENABLE);

  do {
    lsm6dsox_reset_get(&dev_ctx, &rst);
  } while (rst);

  /* Disable I3C interface */
  lsm6dsox_i3c_disable_set(&dev_ctx, LSM6DSOX_I3C_DISABLE);
  /* Enable Block Data Update */
  lsm6dsox_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);

  lsm6dsox_pin_int2_route_get(&dev_ctx, NULL, &int2_route);
  int2_route.drdy_xl = PROPERTY_ENABLE;
  lsm6dsox_pin_int2_route_set(&dev_ctx, NULL, int2_route);

  /* Set Output Data Rate */
  lsm6dsox_xl_data_rate_set(&dev_ctx, LSM6DSOX_XL_ODR_12Hz5);
  lsm6dsox_gy_data_rate_set(&dev_ctx, LSM6DSOX_GY_ODR_12Hz5);
  /* Set full scale */
  lsm6dsox_xl_full_scale_set(&dev_ctx, LSM6DSOX_2g);
  lsm6dsox_gy_full_scale_set(&dev_ctx, LSM6DSOX_2000dps);

  /* Configure filtering chain(No aux interface)
   * Accelerometer - LPF1 + LPF2 path
   */
  //lsm6dsox_xl_hp_path_on_out_set(&dev_ctx, LSM6DSOX_LP_ODR_DIV_100);
  //lsm6dsox_xl_filter_lp2_set(&dev_ctx, PROPERTY_ENABLE);
}

/*
 * @brief  Write generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this examples is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to write
 * @param  bufp      pointer to data to write in register reg
 * @param  len       number of consecutive register to write
 *
 */
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len)
{
  HAL_GPIO_WritePin(SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(handle, &reg, 1, 1000);
  HAL_SPI_Transmit(handle, (uint8_t*) bufp, len, 1000);
  HAL_GPIO_WritePin(SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_SET);
  return 0;
}

/*
 * @brief  Read generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this examples is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to read
 * @param  bufp      pointer to buffer that store the data read
 * @param  len       number of consecutive register to read
 *
 */
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len)
{
  reg |= 0x80;
  HAL_GPIO_WritePin(SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(handle, &reg, 1, 1000);
  HAL_SPI_Receive(handle, bufp, len, 1000);
  HAL_GPIO_WritePin(SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_SET);
  return 0;
}
