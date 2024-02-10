/**
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sub-license, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * File:   sht40x_driver_basic.h
 * Author: Cedric Akilimali
 *
 * Created on April 14, 2023, 22:48 PM
 */

#ifndef SHT40X_DRIVER_BASIC_H_INCLUDED
#define SHT40X_DRIVER_BASIC_H_INCLUDED

#include "sht40x_driver_interface.h"

/**
 * @brief basic example initialize
 * @param[in] variant is the device type
 * @return status code
 *          - 0 success
 *          - 1 initialize failed
 * @note    none
 */
uint8_t sht40x_basic_initialize(sht40x_variant_t variant);

/**
 * @brief     This function get the device variant
 * @param[out] pVariant point to the device variant
 * @return  status code
 *            - 0 success
 *            - 1 failed to get device variant
 * @note      none
 */
uint8_t sht40x_basic_get_variant(sht40x_variant_t *pVariant);

/**
 * @brief     Basic implementation to read the temperature and relative humidity
 * @param[in] precision is the data read accuracy
 * @param[out] pData point to the sensor data to read
 * @return  status code
 *            - 0 success
 *            - 1 failed to get temp/humidity
 * @note      none
 */
uint8_t sht40x_basic_get_temp_rh(sht40x_precision_t precision, sht40x_data_t *pData);

/**
 * @brief     Basic implementation to read the temperature and relative humidity with n number of samples
 * @param[in] precision is the data read accuracy
 * @param[out] pData point to the sensor data to read
 * @param[in] u8NumSample is the number of samples to read
 * @return  status code
 *            - 0 success
 *            - 1 failed to get temp/humidity
 * @note      none
 */
uint8_t sht40x_basic_get_temp_humidity_nSample(sht40x_precision_t precision, sht40x_data_t *pData, uint8_t u8NumSample);

/**
 * @brief     Basic implementation to get the device serial number
 * @param[out] pSerial_Number point to the device serial number
 * @return  status code
 *            - 0 success
 *            - 1 failed to get S/N
 * @note      none
 */
uint8_t sht40x_basic_get_serial_number(uint32_t *pSerial_Number);


/**
 * @brief     Basic implementation to activate heater
 * @param[in]  power is the heater power desired
 * @param[out] pData point to the sensor data to read
 * @return  status code
 *            - 0 success
 *            - 1 failed activate heater
 * @note      none
 */
uint8_t sht40x_basic_activate_heater(sht40x_heater_power_t power, sht40x_data_t *pData);

/**
 * @brief   Basic implementation to soft reset the device
 * @return  status code
 *            - 0 success
 *            - 1 failed to reset
 * @note      none
 */
uint8_t sht40x_basic_soft_reset(void);

/**
 * @brief    Basic implementation to get the address
 * @param[out] pI2c_address point to the chip i2c address
 * @return  status code
 *            - 0 success
 *            - 1 failed to get i2c address
 * @note      none
 */
uint8_t sht40x_basic_get_addr(uint8_t  *pI2c_address);




#endif // SHT40X_DRIVER_BASIC_H_INCLUDED
