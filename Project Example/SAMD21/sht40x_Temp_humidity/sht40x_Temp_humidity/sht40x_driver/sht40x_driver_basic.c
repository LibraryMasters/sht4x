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
 * File:   sht40x_driver_basic.c
 * Author: Cedric Akilimali
 *
 * Created on April 14, 2023, 22:48 PM
 */

#include "sht40x_driver_basic.h"


/**
 * @brief basic example initialize
 * @param[in] variant is the device type
 * @return status code
 *          - 0 success
 *          - 1 initialize failed
 * @note    none
 */

uint8_t sht40x_basic_initialize(sht40x_variant_t variant)
{

    volatile uint8_t err;

    /*link function*/
    DRIVER_SHT40X_LINK_INIT(&sht40x_handler, sht40x_handle_t);                               /**< Link the  */
    DRIVER_SHT40X_LINK_I2C_INIT(&sht40x_handler, sht40x_interface_i2c_init);                 /**< Link the i2c initialize function */
    DRIVER_SHT40X_LINK_I2C_DEINIT(&sht40x_handler, sht40x_interface_i2c_deinit);             /**< Link the the i2c de-initialize function */
    DRIVER_SHT40X_LINK_I2C_WRITE(&sht40x_handler, sht40x_interface_i2c_write);               /**< Link the i2c  write function */
    DRIVER_SHT40X_LINK_I2C_READ(&sht40x_handler, sht40x_interface_i2c_read);                 /**< Link the i2c read function */
    DRIVER_SHT40X_LINK_DELAY_MS(&sht40x_handler,sht40x_interface_delay_ms);                  /**< Link delay function */
    DRIVER_SHT40X_LINK_DEBUG_PRINT(&sht40x_handler, sht40x_interface_debug_print);           /**< Link the the debug print function */

    /* sht40x initialize */
    err = sht40x_init(&sht40x_handler);
    if(err)
    {
        a_sht40x_print_error_msg(&sht40x_handler, "initialize");
        return err;       /**< failed */
    }

    /* set device variant */
    err = sht40x_set_variant(&sht40x_handler, variant);
    if(err)
    {
        a_sht40x_print_error_msg(&sht40x_handler, "set device variant");
        return err;   /**< failed */
    }

    /** set device address */
    err= sht40x_set_addr(&sht40x_handler);
    if(err)
    {
         a_sht40x_print_error_msg(&sht40x_handler, "set device i2c address");
        return err;
    }

    sht40x_interface_delay_ms(10);         /**< wait 10 ms after initialize complete */

    return 0;   /**< success */
}

/**
 * @brief     This function get the device variant
 * @param[out] pVariant point to the device variant
 * @return  status code
 *            - 0 success
 *            - 1 failed to get device variant
 * @note      none
 */
uint8_t sht40x_basic_get_variant(sht40x_variant_t *pVariant)
{

    if(sht40x_get_variant(&sht40x_handler, pVariant) != SHT40X_DRV_OK)
    {
        a_sht40x_print_error_msg(&sht40x_handler, "get device variant");
        return 1; /**< failed */
    }
    return 0;   /**< success*/
}

/**
 * @brief     Basic implementation to read the temperature and relative humidity
 * @param[in] precision is the data read accuracy
 * @param[out] pData point to the sensor data to read
 * @return  status code
 *            - 0 success
 *            - 1 failed to get temp/humidity
 * @note      none
 */
uint8_t sht40x_basic_get_temp_rh(sht40x_precision_t precision, sht40x_data_t *pData)
{
    if(sht40x_get_temp_rh(&sht40x_handler, precision, (uint32_t*) pData) != SHT40X_DRV_OK)
    {
        a_sht40x_print_error_msg(&sht40x_handler, "read data");
        return 1; /**< failed */
    }
    return 0;   /**< success*/
}

/**
 * @brief     Basic implementation to get the device serial number
 * @param[out] pSerial_Number point to the device serial number
 * @return  status code
 *            - 0 success
 *            - 1 failed to get S/N
 * @note      none
 */
uint8_t sht40x_basic_get_serial_number(uint32_t *pSerial_Number)
{
  if(sht40x_get_serial_number(&sht40x_handler, (uint32_t *)pSerial_Number) != SHT40X_DRV_OK)
  {
     a_sht40x_print_error_msg(&sht40x_handler, "read serial number");
     return 1; /**< failed */
  }
  return 0;     /**< success */
}


/**
 * @brief     Basic implementation to activate heater
 * @param[in]  power is the heater power desired
 * @return  status code
 *            - 0 success
 *            - 1 failed activate heater
 * @note      none
 */
uint8_t sht40x_basic_activate_heater(sht40x_heater_power_t power)
{
    if(sht40x_activate_heater(&sht40x_handler, power) != SHT40X_DRV_OK)
    {
         a_sht40x_print_error_msg(&sht40x_handler, "activate heater");
         return 1; /**< failed */
    }
    return 0;   /**< success */

}

/**
 * @brief   Basic implementation to soft reset the device
 * @return  status code
 *            - 0 success
 *            - 1 failed to reset
 * @note      none
 */
uint8_t sht40x_basic_soft_reset(void)
{
    if(sht40x_soft_reset(&sht40x_handler) != SHT40X_DRV_OK)
    {
        a_sht40x_print_error_msg(&sht40x_handler, "soft reset sensor");
         return 1; /**< failed */
    }
    return 0; /**> success */
}

/**
 * @brief    Basic implementation to get the address
 * @param[out] pI2c_address point to the chip i2c address
 * @return  status code
 *            - 0 success
 *            - 1 failed to get i2c address
 * @note      none
 */
uint8_t sht40x_basic_get_addr(uint8_t  *pI2c_address)
{
	if(sht40x_get_addr(&sht40x_handler, (uint8_t *)pI2c_address) != SHT40X_DRV_OK)
	{
		a_sht40x_print_error_msg(&sht40x_handler, "get address");
		 return 1; /**< failed */
	}
	return 0;
}


/* end */
