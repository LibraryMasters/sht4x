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
 * File:   sht40x_driver.c
 * Author: Cedric Akilimali
 *
 * Created on April 14, 2023, 5:38 PM
 */

#include "sht40x_driver.h"

/**
* @brief chip information definition
*/
#define CHIP_NAME                "SHT4x"                 /**< chip name */
#define INTERFACE                 "I2C"                  /**< interface protocol */
#define MANUFACTURER_NAME         "Sensirion"            /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        1.8f                   /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        3.6f                   /**< chip max supply voltage */
#define MIN_CURRENT               0.08                   /**< chip max current (μA)*/
#define MAX_CURRENT               500                    /**< chip min current (μA)*/
#define TEMPERATURE_MIN           -40.0f                 /**< chip min operating temperature (°C) */
#define TEMPERATURE_MAX           125.0f                 /**< chip max operating temperature (°C) */
#define MCU_FLASH_MIN             64                     /**< Micro-controller minimum recommended flash size (kB) */
#define MCU_RAM_MIN               4                      /**< Micro-controller minimum recommended RAM size (KB)*/
#define DRIVER_VERSION            1201                   /**< driver version */

/**
* @brief i2c write byte
* @param[in] *pHandle points to sht40x handle structure
* @param[in] u8Reg is the slave device register address
* @param[in] *pBuf point to data to write
* @param[in] u8Length is the data length to write (number of byte)
* @return status code
            - 0 success
            - 1 failed to write
* @note none
*/
uint8_t a_sht40x_i2c_write(sht40x_handle_t *const pHandle, uint8_t u8Reg, void *pBuf, uint8_t u8Length)
{
    if(pHandle->i2c_write(pHandle->i2c_address, u8Reg, (uint8_t*)pBuf, u8Length) !=  0)
    {
        return 1;                                      /**< return an error if failed to execute */
    }
    return 0;                                          /**< return success */
}

/**
* @brief i2c read byte
* @param[in] *pHandle points to sht40x handle structure
* @param[in] u8Reg is the slave device register address
* @param[out] *pBuf point to data to read
* @param[in] u8Length is the data length to read (number of byte)
* @return status code
*          - 0 success
*          - 1 failed to read
* @note none
*/

uint8_t a_sht40x_i2c_read(sht40x_handle_t  *const pHandle, uint16_t u8Reg, void *pBuf, uint8_t u8Length)
{
    if(pHandle->i2c_read(pHandle->i2c_address, u8Reg, (uint8_t*)pBuf, u8Length) != 0)
    {
        return 1;                                       /**< return an error if failed to execute */
    }
    return 0;                                           /**< return success */
}

/**
* @brief This function prints the error message
* @param[in] *pHandle points to sht40x handle structure
* @param[in] *pBuffer point to the string to be printed
* @return none
* @note   none
*/
void a_sht40x_print_error_msg(sht40x_handle_t *const pHandle, char *const pBuffer)
{
#ifdef SHT40X_DEBUG_MODE
    pHandle->debug_print("sht40x: failed to %s.\r\n", pBuffer);
#endif // SHT40X_DEBUG_MODE
}

/**
 * @brief     This function initialize the chip
 * @param[in] *pHandle points to sht40x pHandle structure
 * @return  status code
 *            - 0 success
 *            - 1 i2c initialization failed
 *            - 2 pHandle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t sht40x_init(sht40x_handle_t *pHandle)
{

    if(pHandle == NULL)
        return 2;     /**< return failed error */
    if(pHandle->debug_print == NULL)
        return 3;      /**< return failed error */

    if(pHandle->delay_ms == NULL)
    {
#ifdef SHT40X_DEBUG_MODE
        pHandle->debug_print("sht40x: delay_ms is null\r\n");
#endif // SHT40X_DEBUG_MODE
        return 3;
    }

    if(pHandle->i2c_init == NULL )
    {
#ifdef SHT40X_DEBUG_MODE
        pHandle->debug_print("sht40x: i2c_init is null\r\n");
#endif // SHT40X_DEBUG_MODE
        return 3;
    }

    if(pHandle->i2c_deinit == NULL )
    {
#ifdef SHT40X_DEBUG_MODE
        pHandle->debug_print("sht40x: i2c_deinit is null\r\n");
#endif // SHT40X_DEBUG_MODE
        return 3;
    }

    if(pHandle->i2c_read == NULL )
    {
#ifdef SHT40X_DEBUG_MODE
        pHandle->debug_print("sht40x: i2c_read is null\r\n");
#endif // SHT40X_DEBUG_MODE
        return 3;
    }

    if(pHandle->i2c_write == NULL )
    {
#ifdef SHT40X_DEBUG_MODE
        pHandle->debug_print("sht40x: i2c_write is null\r\n");
#endif // SHT40X_DEBUG_MODE
        return 3;
    }

    if(pHandle->i2c_init())
    {
        a_sht40x_print_error_msg(pHandle, "initialize i2c");
        return 1 ;
    }
    pHandle->inited = 1;
    return 0;                   /**< return success */
}

/**
 * @brief     This function close the chip
 * @param[in] *pHandle points to sht40x pHandle structure
 * @return  status code
 *            - 0 success
 *            - 1 i2c deinit failed
 *            - 2 pHandle is NULL
 *            - 3 pHandle is not initialized
 * @note      none
 */
uint8_t sht40x_deinit(sht40x_handle_t *pHandle)
{
    if(pHandle == NULL)
        return 2;     /**< return failed error */
    if(pHandle->inited != 1)
        return 3;      /**< return failed error */

    if(pHandle->i2c_deinit() != 0)
    {
        a_sht40x_print_error_msg(pHandle, "de-initialize i2c");
        return 1;
    }
    pHandle->inited = 0;
    return 0;
}

/**
 * @brief     This function set the i2c address
 * @param[in] *pHandle points to sht40x pHandle structure
 * @return  status code
 *            - 0 success
 *            - 1 failed to set i2c address
 *            - 2 pHandle is NULL
 *            - 3 pHandle is not initialized
 * @note      none
 */
uint8_t sht40x_set_addr(sht40x_handle_t *const pHandle)
{

    if(pHandle == NULL)
        return 2;     /**< return failed error */
    if(pHandle->inited != 1)
        return 3;      /**< return failed error */

    pHandle->i2c_address = pHandle->addres;
    if(pHandle->i2c_address !=  pHandle->addres)
    {
        a_sht40x_print_error_msg(pHandle, "set i2c address");
        return 1;           /*< failed */
    }

    return 0;     /*< success */
}

/**
 * @brief     This function get the i2c address
 * @param[in] *pHandle points to sht40x pHandle structure
 * @param[out] pI2c_address point to the chip i2c address
 * @return  status code
 *            - 0 success
 *            - 1 failed to get i2c address
 *            - 2 pHandle is NULL
 *            - 3 pHandle is not initialized
 * @note      none
 */
uint8_t sht40x_get_addr(sht40x_handle_t *const pHandle, sht40x_i2c_address_t  *pI2c_address)
{
    if(pHandle == NULL)
        return 2;     /**< return failed error */
    if(pHandle->inited != 1)
        return 3;      /**< return failed error */

    *pI2c_address = (sht40x_i2c_address_t)pHandle->i2c_address;     /**< read i2c set address */
    if(*pI2c_address != pHandle->i2c_address)
    {
        a_sht40x_print_error_msg(pHandle, "get i2c address");
        return 1;           /**<failed */
    }
    return 0;               /**<success */
}

/**
 * @brief     This function set the device variant
 * @param[in] *pHandle points to sht40x pHandle structure
 * @param[in] variant is the device variant
 * @return  status code
 *            - 0 success
 *            - 1 failed to set device variant
 *            - 2 pHandle is NULL
 *            - 3 pHandle is not initialized
 * @note      none
 */
uint8_t sht40x_set_variant(sht40x_handle_t *const pHandle, sht40x_variant_t variant)
{

    if(pHandle == NULL)
        return 2;     /**< return failed error */
    if(pHandle->inited != 1)
        return 3;      /**< return failed error */

    pHandle->variant = variant;
    if(pHandle->variant != variant)
    {
        a_sht40x_print_error_msg(pHandle, "set device variant");
        return 1;   /**< failed*/
    }

    switch(variant)
    {

        case SHT40_AD1B_VARIANT:
        {
            pHandle->addres = (sht40x_i2c_address_t)SHT40_AD1B_IIC_ADDRESS;
            break;
        }


        case SHT40_BD1B_VARIANT:
        {
            pHandle->addres = (sht40x_i2c_address_t)SHT40_BD1B_IIC_ADDRESS;
            break;
        }


        case SHT41_AD1B_VARIANT:
        {
            pHandle->addres = (sht40x_i2c_address_t)SHT41_AD1B_IIC_ADDRESS;
            break;
        }


        case SHT45_AD1B_VARIANT:
        {
            pHandle->addres = (sht40x_i2c_address_t)SHT45_AD1B_IIC_ADDRESS;
            break;
        }

    }

    return 0;   /**< success */
}

/**
 * @brief     This function get the device variant
 * @param[in] *pHandle points to sht40x pHandle structure
 * @param[out] pVariant point to the device variant
 * @return  status code
 *            - 0 success
 *            - 1 failed to get device variant
 *            - 2 pHandle is NULL
 *            - 3 pHandle is not initialized
 * @note      none
 */
uint8_t sht40x_get_variant(sht40x_handle_t *const pHandle, sht40x_variant_t *pVariant)
{

    if(pHandle == NULL)
        return 2;     /**< return failed error */
    if(pHandle->inited != 1)
        return 3;      /**< return failed error */

    *pVariant = (sht40x_variant_t)pHandle->variant ;
    if(*pVariant != (sht40x_variant_t)pHandle->variant)
    {
        a_sht40x_print_error_msg(pHandle, "get device variant");
        return 1;       /**< failed*/
    }

    return 0;           /**< success */
}

/**
 * @brief     This function reads the temperature and humidity
 * @param[in] *pHandle points to the sht40x pHandler structure
 * @param[in] precision is the data read accuracy
 * @param[out] pData point to the sensor data to read
 * @return  status code
 *            - 0 success
 *            - 1 failed to get temp/humidity
 *            - 2 pHandle is NULL
 *            - 3 pHandle is not initialized
 * @note      none
 */
uint8_t sht40x_get_temp_rh(sht40x_handle_t *const pHandle,  sht40x_precision_t precision, sht40x_data_t *pData)
{
    uint8_t err;
    uint8_t pStatus[RESPONSE_LENGTH];

    if(pHandle == NULL)
        return 2;     /**< return failed error */
    if(pHandle->inited != 1)
        return 3;      /**< return failed error */

    err = a_sht40x_i2c_write(pHandle, READ_PRECISION[precision], DUMMY_DATA, 0);
    if(err)
    {
        a_sht40x_print_error_msg(pHandle, "write temp and humidity cmd");
        return err;  /**< failed*/
    }

    pHandle->delay_ms(10);      /**< wait 10 ms for conversion to complete */

    err = a_sht40x_i2c_read(pHandle, DUMMY_DATA, (uint8_t *)pStatus, RESPONSE_LENGTH);  /**< read result */
    if(err)
    {
        a_sht40x_print_error_msg(pHandle, "read temp and humidity");
        return err;  /**< failed*/
    }
    pData->temperature_C = (pStatus[0] << 8) |  pStatus[1];
    pData->temperature_C = ((pData->temperature_C/65535.0) * 175) - 45;
    pData->temperature_F = (pData->temperature_C * 9/5) + 32;

    pData->humidity = (pStatus[3] << 8) | pStatus[4];
    pData->humidity = ((pData->humidity/65535.0) * 125) - 6;

        /**error handler***/
    pData->humidity =  pData->humidity > HUMIDITY_MAX ? HUMIDITY_MAX: pData->humidity;                     /**< if humidity is high than max allowed, set to 100 */
    pData->humidity =  pData->humidity < HUMIDITY_MIN ? HUMIDITY_MIN:  pData->humidity;                    /**< if humidity is less than min allowed, set to 0 */

    memcpy(pData->rawData, pStatus, RESPONSE_LENGTH);

    return 0;
}

/**
 * @brief     This function get the device serial number
 * @param[in] *pHandle points to sht40x pHandle structure
 * @param[out] pSerial_Number point to the device serial number
 * @return  status code
 *            - 0 success
 *            - 1 failed to get S/N
 *            - 2 pHandle is NULL
 *            - 3 pHandle is not initialized
 * @note      none
 */
uint8_t sht40x_get_serial_number(sht40x_handle_t *const pHandle, uint32_t *pSerial_Number)
{
    uint8_t err;
    uint8_t temp_data[4];         /**< temporary data to hold serial number */
    uint8_t count = 3;
    uint8_t dataOut[4];
    int index;

    if(pHandle == NULL)
        return 2;     /**< return failed error */
    if(pHandle->inited != 1)
        return 3;      /**< return failed error */

    memset(temp_data, 0, 4);

     err = a_sht40x_i2c_write(pHandle, SHT40X_READ_SERIAL_NUMBER_CMD, DUMMY_DATA, 0);
    if(err)
    {
        a_sht40x_print_error_msg(pHandle, "write UID cmd");
        return err;  /**< failed*/
    }

    pHandle->delay_ms(10);

    err = a_sht40x_i2c_read(pHandle, DUMMY_DATA, (uint8_t *)temp_data, RESPONSE_LENGTH);
    if(err)
    {
        a_sht40x_print_error_msg(pHandle, "get UID");
        return err;  /**< failed*/
    }

	temp_data[2] = temp_data[3];
	temp_data[3] = temp_data[4];

  for( index = 0; index < 4; ++index)
    {
        dataOut[count] = temp_data[index];     /**< move data into a temporarily buffer in reverse order*/
        count--;
    }
   memcpy(serial.pBuffer, dataOut, 4);
  *pSerial_Number = serial.raw;

    return 0;           /**< success */
}

/**
 * @brief     This function activate the device heater
 * @param[in] *pHandle points to sht40x pHandle structure
 * @param[in]  power is the heater power desired
 * @param[out] pData point to the sensor data to read
 * @return  status code
 *            - 0 success
 *            - 1 failed activate heater
 *            - 2 pHandle is NULL
 *            - 3 pHandle is not initialized
 * @note      Depending on heater setting selected, this routine can take up to 1000 ms delay
 */
uint8_t sht40x_activate_heater(sht40x_handle_t *const pHandle, sht40x_heater_power_t power, sht40x_data_t *pData)
{

    uint8_t err;
    uint8_t pStatus[RESPONSE_LENGTH];


    if(pHandle == NULL)
        return 2;     /**< return failed error */
    if(pHandle->inited != 1)
        return 3;      /**< return failed error */

         err = a_sht40x_i2c_write(pHandle, HEATER_POWER[power], DUMMY_DATA, 0);
    if(err)
    {
        a_sht40x_print_error_msg(pHandle, "write heater cmd");
        return err;  /**< failed*/
    }

    if((power == SHT40X_HEATER_POWER_200mW_1S) || (power == SHT40X_HEATER_POWER_110mW_1S) || (power == SHT40X_HEATER_POWER_20mW_1S))
        pHandle->delay_ms(HEATER_DELAY_1S);
    else
     pHandle->delay_ms(HEATER_DELAY_100mS);

    err = a_sht40x_i2c_read(pHandle, DUMMY_DATA, (uint8_t *)pStatus, RESPONSE_LENGTH);
    if(err)
    {
        a_sht40x_print_error_msg(pHandle, "read temp and humidity");
        return err;  /**< failed*/
    }

    pData->temperature_C = (pStatus[0] << 8) |  pStatus[1];
    pData->temperature_C = ((pData->temperature_C/65535.0) * 175) - 45;
    pData->temperature_F = (pData->temperature_C * 9/5) + 32;

    pData->humidity = (pStatus[3] << 8) | pStatus[4];
    pData->humidity = ((pData->humidity/65535.0) * 125) - 6;

    memcpy(pData->rawData, pStatus, RESPONSE_LENGTH);

    /**error handler***/

    pData->humidity =  pData->humidity > HUMIDITY_MAX ? HUMIDITY_MAX: pData->humidity;                     /**< if humidity is high than max allowed, set to 100 */
    pData->humidity =  pData->humidity < HUMIDITY_MIN ? HUMIDITY_MIN:  pData->humidity;                     /**< if humidity is less than min allowed, set to 0 */

    return 0;


    return 0;
}

/**
 * @brief     This function soft reset the device
 * @param[in] *pHandle points to sht40x pHandle structure
 * @return  status code
 *            - 0 success
 *            - 1 failed to reset
 *            - 2 pHandle is NULL
 *            - 3 pHandle is not initialized
 * @note      none
 */
uint8_t sht40x_soft_reset(sht40x_handle_t *const pHandle)
{
    uint8_t err;

    if(pHandle == NULL)
        return 2;     /**< return failed error */
    if(pHandle->inited != 1)
        return 3;      /**< return failed error */

    err = a_sht40x_i2c_write(pHandle, SHT40X_SOFT_RESET_CMD, DUMMY_DATA, 0);
    if(err)
    {
        a_sht40x_print_error_msg(pHandle, "to reset");
        return err;     /**< failed */
    }

    return 0;           /**< success */
}


/**
 * @brief      get chip's information
 * @param[out] *pInfo points to sht40x info structure
 * @return  status code
 *             - 0 success
 *             - 2 pHandle is NULL
 * @note       none
 */
uint8_t sht40x_info(sht40x_info_t *const pInfo)
{
    if (pInfo == NULL)     /**< check if handle is null */
    {
        return 2;              /**<failed, return error */
    }
    memset(pInfo, 0, sizeof (sht40x_info_t));                        /**< initialize sht40x info structure */
    strncpy(pInfo->chip_name, CHIP_NAME, 10);                        /**< copy chip name */
    strncpy(pInfo->interface, INTERFACE, 8);                         /**< copy interface name */
    strncpy(pInfo->manufacturer_name, MANUFACTURER_NAME, 25);        /**< copy manufacturer name */
    pInfo->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /**< set minimal supply voltage */
    pInfo->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /**< set maximum supply voltage */
    pInfo->max_current_ma = MAX_CURRENT;                             /**< set maximum current */
    pInfo->temperature_max = TEMPERATURE_MAX;                        /**< set minimal temperature */
    pInfo->temperature_min = TEMPERATURE_MIN;                        /**< set maximum temperature */
    pInfo->flash_size_min = MCU_FLASH_MIN;                           /**< set the Micro-controller minimum recommended flash size */
    pInfo->ram_size_min = MCU_RAM_MIN;                               /**< set the Micro-controller minimum recommended ram size */
    pInfo->driver_version = DRIVER_VERSION;                          /**< set driver version */

    return 0;                                                        /**< return success */
}

/**
 * @}
 */

/*end*/

