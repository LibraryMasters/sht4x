#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "sht4x_driver/src/sht40x_driver_basic.h"

sht40x_info_t sht40xInfo;
sht40x_data_t dataRead;

int err;                        
uint32_t UID;                        /**< will hold the sensor unique ID*/                   
uint8_t variant;                     /**< will hold the sensor variant (as an int) */
uint8_t deviceAdd;                   /**< holds the device address when read*/         
uint8_t NumberSamples = 10;          /**< number of samples to read */

uint8_t i2c_write(uint8_t addr, uint8_t reg, uint8_t *pBuf, uint16_t len);
uint8_t i2c_read(uint8_t addr, uint8_t reg, uint8_t *pBuf, uint16_t len);

int main()
{
    stdio_init_all();

    // This example will use I2C0 on the default SDA and SCL pins (4, 5 on a Pico)

    i2c_init(i2c_default, 100 * 1000);             /*< 100Khz Baudrate*/
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    sht40x_basic_initialize(SHT40_AD1B_VARIANT);
    sht40x_info(&sht40xInfo);

    sht40x_interface_delay_ms(3000);

    sht40x_interface_debug_print("Chip Name: \t%s\r\n", sht40xInfo.chip_name);
    sht40x_interface_debug_print("Manufacturer: \t%s\r\n", sht40xInfo.manufacturer_name);
    sht40x_interface_debug_print("Interface Protocol: \t%s\r\n", sht40xInfo.interface);
    sht40x_interface_debug_print("Supply Volt Max: \t%.1f V\r\n", sht40xInfo.supply_voltage_max_v);
    sht40x_interface_debug_print("Supply Volt Min: \t%.1f V\r\n", sht40xInfo.supply_voltage_min_v);
    sht40x_interface_debug_print("Maximum Current: \t%.1f uA\r\n", sht40xInfo.max_current_ma);
    sht40x_interface_debug_print("Max Temperature: \t%.1f C\r\n", sht40xInfo.temperature_max);
    sht40x_interface_debug_print("Diver Version: \t\tV%.1f.%.2d\r\n", (sht40xInfo.driver_version / 1000), (uint8_t) (sht40xInfo.driver_version - (uint8_t) (sht40xInfo.driver_version / 100)*100));
    sht40x_interface_debug_print("\nRecommended MCU flash: \t%dkB\r\n",sht40xInfo.flash_size_min);
    sht40x_interface_debug_print("Recommended MCU RAM: \t%dkB\r\n",sht40xInfo.ram_size_min);

    while (1)
    {
		err =  sht40x_basic_get_temp_rh(SHT40X_PRECISION_HIGH, &dataRead);                               /**< Take temperature and humidity measurement */
		sht40x_interface_debug_print("\nTemp C: %.2f\n", dataRead.temperature_C);
		sht40x_interface_debug_print("Temp F: %.2f\n", dataRead.temperature_F);
		sht40x_interface_debug_print("Humidity: %.2f\n", dataRead.humidity);
		
		for(int index = 0; index < RESPONSE_LENGTH; index++){
			sht40x_interface_debug_print("raw data: 0x%.2x\n", dataRead.rawData[index]);
		}
		
		err = sht40x_basic_get_serial_number( (uint32_t*)&UID);                                         /**< Read sensor unique ID (Serial number) */
        sht40x_interface_debug_print("Device S/N: %lu\n", UID);

        sht40x_interface_delay_ms(3000);


       err = sht40x_basic_get_temp_humidity_nSample(SHT40X_PRECISION_HIGH, &dataRead, NumberSamples); /**< Measure Temp and humidity with n number of samples */
       sht40x_interface_debug_print("\nTemp C sampled: %.2f\n", dataRead.temperature_C);
       sht40x_interface_debug_print("Temp f sampled: %.2f\n", dataRead.temperature_F);
       sht40x_interface_debug_print("Humidity sampled: %.2f\n", dataRead.humidity);

//        err = sht40x_basic_activate_heater(SHT40X_HEATER_POWER_200mW_100mS, &dataRead);                 /**< Activate heater and measure temperature */
//        sht40x_interface_debug_print("\nHeater Temp C: %.2f\n", dataRead.temperature_C);
//        sht40x_interface_debug_print("Heater Temp F: %.2f\n", dataRead.temperature_F);
//        sht40x_interface_debug_print("Heater Humidity: %.2f\n", dataRead.humidity);

       sht40x_basic_get_variant((uint8_t *) & variant);
       sht40x_interface_debug_print("\nDevice variant: %d\n", variant);
       sht40x_basic_get_addr((uint8_t *) & deviceAdd);
       sht40x_interface_debug_print("\nDevice Address: 0x%x\n", deviceAdd);
    }
    return 0;
}

/**
 * @brief This function re-format the i2c write function to be implemented into the sht4x driver
 * 
 * @param addr is the device slave address 
 * @param reg is the register to write
 * @param pBuf point to data to write to the sensor
 * @param len is the number of byte to write
 * @return none 
 */
uint8_t i2c_write(uint8_t addr, uint8_t reg, uint8_t *pBuf, uint16_t len)
{
 i2c_write_blocking(i2c_default, addr, (uint8_t*)&reg, 1, false);
}

/**
 * @brief This function re-format the i2c read function to be implemented into the sht4x driver
 * 
 * @param addr is the device slave address 
 * @param reg is the register to read
 * @param pBuf point to data read from the sensor
 * @param len is the number of byte to read
 * @return none 
 */
uint8_t i2c_read(uint8_t addr, uint8_t reg, uint8_t *pBuf, uint16_t len)
{
    i2c_read_blocking(i2c_default, addr, (uint8_t *)pBuf, len, false);
}
