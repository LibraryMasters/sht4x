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
 * File:   sht40x_driver.h
 * Author: Cedric Akilimali
 *
 * Created on April 14, 2023, 4:13 PM
 */
#ifndef SHT40X_DRIVER_H_INCLUDED
#define SHT40X_DRIVER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>

#define SHT40X_DEBUG_MODE

/**
 * @defgroup driver_sht40x mcp23x08 driver function
 * @brief sht40x driver modules
 * @{
 */

/**
 * @addtogrouup sht40x_base_driver
 * @{
 */

 /** Register */
 #define SHT40X_RESET_REG                                   0x00                /**< reset register address */

 /*Control command */

 #define SHT40X_MEASURE_T_RH_HIGH_PREC_CMD                  0xFD                /**< Measure T & RH with high precision (high repeatability) command */
 #define SHT40X_MEASURE_T_RH_MIDIUM_PREC_CMD                0xF6                /**< Measure T & RH with medium precision (medium repeatability) command */
 #define SHT40X_MEASURE_T_RH_LOWEST_PREC_CMD                0xE0                /**< Measure T & RH with lowest precision (low repeatability) command */
 #define SHT40X_READ_SERIAL_NUMBER_CMD                      0x89                /**< Read serial number command*/
 #define SHT40X_SOFT_RESET_CMD                              0x94                /**< Soft reset activate heater with 200mW for 1s, including a high precision measurement just before deactivation*/
 #define SHT40X_ACTIVATE_HEATER_200mW_1_S_CMD               0x39                /**< Activate heater with 200mW for 0.1s including a high precision measurement just before deactivation */
 #define SHT40X_ACTIVATE_HEATER_200mW_100mS_CMD             0x32                /**< Activate heater with 110mW for 1s including a high precision measurement just before deactivation */
 #define SHT40X_ACTIVATE_HEATER_110mW_1_S_CMD               0x2F                /**< Activate heater with 110mW for 0.1s including a high precision measurement just before deactivation */
 #define SHT40X_ACTIVATE_HEATER_110mW_100mS_CMD             0x24                /**< Activate heater with 110mW for 0.1s including a high precision measurement just before deactivation*/
 #define SHT40X_ACTIVATE_HEATER_20mW_1_S_CMD                0x1E                /**< activate heater with 20mW for 1s including a high precision measurement just before deactivation*/
 #define SHT40X_ACTIVATE_HEATER_20mW_100mS_CMD              0x15                /**< Activate heater with 20mW for 0.1s including a high precision measurement just before deactivation*/

 /* Response length */
 #define RESPONSE_LENGTH                                    0x06                /*< I2C response length */

 #define DUMMY_DATA                                         0x00                 /**< dummy data */

 #define HUMIDITY_MIN                                       0U
 #define HUMIDITY_MAX                                       100U

/* Read precision table */
static uint8_t  const READ_PRECISION[3] = { SHT40X_MEASURE_T_RH_HIGH_PREC_CMD,
                              SHT40X_MEASURE_T_RH_MIDIUM_PREC_CMD,
                              SHT40X_MEASURE_T_RH_LOWEST_PREC_CMD
                            };

/* Heater activate power table */
static uint8_t const HEATER_POWER[6] = { SHT40X_ACTIVATE_HEATER_200mW_1_S_CMD,
                            SHT40X_ACTIVATE_HEATER_200mW_100mS_CMD,
                            SHT40X_ACTIVATE_HEATER_110mW_1_S_CMD,
                            SHT40X_ACTIVATE_HEATER_110mW_100mS_CMD,
                            SHT40X_ACTIVATE_HEATER_20mW_1_S_CMD,
                            SHT40X_ACTIVATE_HEATER_20mW_100mS_CMD
                           };

                           /**
* @brief execution status enumeration
*/
typedef enum
{
   SHT40X_DRV_OK          = 0x00,                                     /**< status execute success */
   SHT40X_DRV_FAILED      = 0x01,                                     /**< status execute failed */
   SHT40X_DRV_ERR_HANDLER = 0x02,                                     /**< status execute failed, handle is null */
   SHT40X_DRV_ERR_INIT    = 0x03                                      /**< status execute failed, handle not initialize */
} sht40x_driver_execute_stat_t;

 /**
 * @brief sht40x variant enumeration
 */
typedef enum {
    SHT40_AD1B_VARIANT = 0x00,              /**< */
    SHT40_BD1B_VARIANT = 0x01,              /**< */
    SHT41_AD1B_VARIANT = 0x02,              /**< */
    SHT45_AD1B_VARIANT = 0x03               /**< */
}sht40x_variant_t;


 /**
 * @brief sht40x i2c address enumeration
 */
typedef enum {
    SHT40_AD1B_IIC_ADDRESS = 0x44,           /**< */
    SHT40_BD1B_IIC_ADDRESS = 0x45,           /**< */
    SHT41_AD1B_IIC_ADDRESS = 0x44,           /**< */
    SHT45_AD1B_IIC_ADDRESS = 0x44            /**< */
}sht40x_i2c_address_t;

 /**
 * @brief sht40x boolean enumeration
 */
typedef enum
{
    SHT40X_BOOL_FALSE  = 0x00,                                                 /**< boolean state false */
    SHT40X_BOOL_TRUE   = 0x01                                                  /**< boolean state true */
}sht40x_bool_t;

 /**
 * @brief sht40x read precision enumeration
 */
typedef enum{
    SHT40X_PRECISION_HIGH   = 0x00,                                             /**< */
    SHT40X_PRECISION_MIDIUM = 0x01,                                             /**< */
    SHT40X_PRECISION_LOWEST = 0x02                                              /**< */
}sht40x_precision_t;

 /**
 * @brief sht40x heater power enumeration
 */
typedef enum{
    SHT40X_HEATER_POWER_200mW_1S    = 0x00,                                     /**< */
    SHT40X_HEATER_POWER_200mW_100mS = 0x01,                                     /**< */
    SHT40X_HEATER_POWER_110mW_1S    = 0x02,                                     /**< */
    SHT40X_HEATER_POWER_110mW_100mS = 0x03,                                     /**< */
    SHT40X_HEATER_POWER_20mW_1S     = 0x04,                                     /**< */
    SHT40X_HEATER_POWER_20mW_100mS  = 0x05                                      /**< */
}sht40x_heater_power_t;

/**
* @brief sht40x data structure definition
*/
 typedef struct sht40x_data_s
 {
    float temperature_C;                                                          /**< */
    float temperature_F;                                                          /**< */
    float humidity;                                                             /**< */
    uint8_t pTempRawData[2];                                                    /**< */
    uint8_t pHumidityRawData[2];                                                /**< */

 }sht40x_data_t;

 /**
 * @brief sht40x unique ID union definition
 */
 union
{
    uint8_t pBuffer[4];                                                       /**< */
    uint32_t raw;                                                             /**< */

}static serial;

 /**
* @brief sht40x handle enumeration
*/
typedef struct  sht40x_handle_s
{
    uint8_t (*i2c_init)(void);                                                                  /**< point to a i2c init function address */
    uint8_t (*i2c_deinit)(void);                                                                /**< point to a i2c deinit function address */
    uint8_t (*i2c_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);                 /**< point to a i2c read function address */
    uint8_t (*i2c_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);                /**< point to a i2c write function address */
    void (*delay_ms)(uint32_t u32Ms);                                                           /**< point to a delay_ms function address */
    void(*debug_print)(char *fmt, ...);                                                         /**< point to a debug_print function address */
    uint8_t i2c_address;                                                                        /**< i2c device address */
    uint8_t variant;                                                                            /**< sensor variant */
    uint8_t inited;
    sht40x_i2c_address_t addres;
} sht40x_handle_t;


 /**
 * @brief sht40x information structure definition
 */
typedef struct sht40x_info_s
{
    char chip_name[10];                                                         /**< chip name */
    char manufacturer_name[25];                                                 /**< manufacturer name */
    char interface[5];                                                          /**< chip interface name */
    float supply_voltage_min_v;                                                 /**< chip min supply voltage */
    float supply_voltage_max_v;                                                 /**< chip max supply voltage */
    float max_current_ma;                                                       /**< chip max current */
    float temperature_min;                                                      /**< chip min operating temperature */
    float temperature_max;                                                      /**< chip max operating temperature */
    float driver_version;                                                       /**< driver version */
} sht40x_info_t;

 /**
 * @}
 */

/**
* @defgroup sht40x_link_driver sht40x link driver function
* @brief    sht40x link driver modules
* @ingroup  sht40x driver
* @{
*/

/**
 * @brief     initialize sht40x_handle_t structure
 * @param[in] pHandle points to sht40x pHandle structure
 * @param[in] STRUCTURE is sht40x_handle_t
 * @note      none
 */
#define DRIVER_SHT40X_LINK_INIT(pHandle, STRUCTURE)           memset(pHandle, 0, sizeof(STRUCTURE))

/**
 * @brief     link i2c_init function
 * @param[in] pHandle points to sht40x pHandle structure
 * @param[in] FUC points to a i2c_init function address
 * @note      none
 */
#define DRIVER_SHT40X_LINK_I2C_INIT(pHandle, FUC)              (pHandle)->i2c_init = FUC


/**
 * @brief     link i2c_deinit function
 * @param[in] pHandle points to sht40x pHandle structure
 * @param[in] FUC points to a i2c_deinit function address
 * @note      none
 */
#define DRIVER_SHT40X_LINK_I2C_DEINIT(pHandle, FUC)            (pHandle)->i2c_deinit = FUC


/**
 * @brief     link i2c_write function
 * @param[in] pHandle points to sht40x pHandle structure
 * @param[in] FUC points to a i2c_write function address
 * @note      none
 */
#define DRIVER_SHT40X_LINK_I2C_WRITE(pHandle, FUC)             (pHandle)->i2c_write = FUC


/**
 * @brief     link i2c_read function
 * @param[in] pHandle points to sht40x pHandle structure
 * @param[in] FUC points to a i2c_read function address
 * @note      none
 */
#define DRIVER_SHT40X_LINK_I2C_READ(pHandle, FUC)              (pHandle)->i2c_read = FUC

/**
 * @brief     link delay_ms function
 * @param[in] pHandle points to sht40x pHandle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_SHT40X_LINK_DELAY_MS(pHandle, FUC)             (pHandle)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] pHandle points to sht40x pHandle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_SHT40X_LINK_DEBUG_PRINT(pHandle, FUC)          (pHandle)->debug_print = FUC

/**
 * @}
 */


 /**
* @defgroup sht40x_base_driver sht40x base driver function
* @brief    sht40x base driver modules
* @ingroup  mcp23x08_driver
* @{
*/

/**
 * @brief      get chip's information
 * @param[out] *info points to sht40x info structure
 * @return  status code
 *             - 0 success
 *             - 2 pHandle is NULL
 * @note       none
 */
uint8_t sht40x_info(sht40x_info_t *const info);

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
uint8_t sht40x_init(sht40x_handle_t *const pHandle);

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
uint8_t sht40x_deinit(sht40x_handle_t *const pHandle);

/**
 * @brief     This function set the address
 * @param[in] *pHandle points to sht40x pHandle structure
 * @return  status code
 *            - 0 success
 *            - 1 failed to set i2c address
 *            - 2 pHandle is NULL
 *            - 3 pHandle is not initialized
 * @note      none
 */
uint8_t sht40x_set_addr(sht40x_handle_t *const pHandle);

/**
 * @brief     This function get the address
 * @param[in] *pHandle points to sht40x pHandle structure
 * @param[out] pI2c_address point to the chip i2c address
 * @return  status code
 *            - 0 success
 *            - 1 failed to get i2c address
 *            - 2 pHandle is NULL
 *            - 3 pHandle is not initialized
 * @note      none
 */
uint8_t sht40x_get_addr(sht40x_handle_t *const pHandle, sht40x_i2c_address_t  *pI2c_address);

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
uint8_t sht40x_set_variant(sht40x_handle_t *const pHandle, sht40x_variant_t variant);

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
uint8_t sht40x_get_variant(sht40x_handle_t *const pHandle, sht40x_variant_t *pVariant);

/**
 * @brief     This function reads the temperature and humidity
 * @param[in] *pHandle points to sht40x pHandle structure
 * @param[in] precision is the data read accuracy
 * @param[out] pData point to the sensor data to read
 * @return  status code
 *            - 0 success
 *            - 1 failed to get temp/humidity
 *            - 2 pHandle is NULL
 *            - 3 pHandle is not initialized
 * @note      none
 */
uint8_t sht40x_get_temp_rh(sht40x_handle_t *const pHandle,  sht40x_precision_t precision, sht40x_data_t *pData);

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
uint8_t sht40x_get_serial_number(sht40x_handle_t *const pHandle, uint32_t *pSerial_Number);

/**
 * @brief     This function activate the device heater
 * @param[in] *pHandle points to sht40x pHandle structure
 * @param[in]  power is the heater power desired
 * @return  status code
 *            - 0 success
 *            - 1 failed activate heater
 *            - 2 pHandle is NULL
 *            - 3 pHandle is not initialized
 * @note      none
 */
uint8_t sht40x_activate_heater(sht40x_handle_t *const pHandle, sht40x_heater_power_t power);

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
uint8_t sht40x_soft_reset(sht40x_handle_t *const pHandle);










#endif // SHT40X_DRIVER_H_INCLUDED
