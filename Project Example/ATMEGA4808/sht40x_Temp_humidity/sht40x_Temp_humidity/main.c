#include <atmel_start.h>
#include <util/delay.h>
#include "sht40x_driver_basic.h"

sht40x_info_t sht40xInfo;
sht40x_data_t dataRead;

uint32_t UID;
uint8_t variant;
uint8_t deviceAdd;
uint8_t NumberSamples = 10;

uint8_t i2c_write(uint8_t addr, uint8_t *pBuf, uint8_t len);
uint8_t i2c_read(uint8_t addr, uint8_t *pBuf, uint8_t len);
void delay_ms(uint32_t u32Ms);

int main(void)
{
	/* Initializes MCU, drivers and middle-ware */
	atmel_start_init();
	
	sht40x_basic_initialize(SHT40_AD1B_VARIANT);
	sht40x_info(&sht40xInfo);
	
	sht40x_interface_debug_print("Chip Name: \t%s\r\n", sht40xInfo.chip_name);
	sht40x_interface_debug_print("Manufacturer: \t%s\r\n",sht40xInfo.manufacturer_name);
	sht40x_interface_debug_print("Interface Protocol: \t%s\r\n", sht40xInfo.interface);
	sht40x_interface_debug_print("Supply Volt Max: \t%.1f V\r\n",sht40xInfo.supply_voltage_max_v);
	sht40x_interface_debug_print("Supply Volt Min: \t%.1f V\r\n",sht40xInfo.supply_voltage_min_v);
	sht40x_interface_debug_print("Maximum Current: \t%.1f uA\r\n",sht40xInfo.max_current_ma);
	sht40x_interface_debug_print("Max Temperature: \t%.1f C\r\n",sht40xInfo.temperature_max);
	sht40x_interface_debug_print("Diver Version: \t\tV%.1f.%.2d\r\n",(sht40xInfo.driver_version /1000), (uint8_t)(sht40xInfo.driver_version - (uint8_t)(sht40xInfo.driver_version / 100)*100));
	

	/* Replace with your application code */
	while (1) {
		LED_GREEN_toggle_level();
		sht40x_interface_delay_ms(3000);
		
		err =  sht40x_basic_get_temp_rh(SHT40X_PRECISION_HIGH, &dataRead);                                       /**< Take temperature and humidity measurement */
		sht40x_interface_debug_print("\nTemp C: %.2f\n", dataRead.temperature_C);
		sht40x_interface_debug_print("Temp F: %.2f\n", dataRead.temperature_F);
		sht40x_interface_debug_print("Humidity: %.2f\n", dataRead.humidity);
		
		for(int index = 0; index < RESPONSE_LENGTH; index++){
			sht40x_interface_debug_print("raw data: 0x%.2x\n", dataRead.rawData[index]);
		}
		
		err = sht40x_basic_get_serial_number( (uint32_t*)&UID );                                                 /**< Read sensor unique ID (Serial number) */
		sht40x_interface_debug_print("\nserial number : %lu\n", UID);
		

		//        err = sht40x_basic_get_temp_humidity_nSample(SHT40X_PRECISION_HIGH, &dataRead, NumberSamples); /**< Measure Temp and humidity with n number of samples */
		//        sht40x_interface_debug_print("\nTemp C sampled: %.2f\n", dataRead.temperature_C);
		//        sht40x_interface_debug_print("Humidity sampled: %.2f\n", dataRead.humidity);

		//        err = sht40x_basic_activate_heater(SHT40X_HEATER_POWER_200mW_100mS, &dataRead);                 /**< Activate heater and measure temperature */
		//        sht40x_interface_debug_print("\nHeater Temp C: %.2f\n", dataRead.temperature_C);
		//        sht40x_interface_debug_print("Heater Temp F: %.2f\n", dataRead.temperature_F);
		//        sht40x_interface_debug_print("Heater Humidity: %.2f\n", dataRead.humidity);

		//        sht40x_basic_get_variant((uint8_t *) & variant);
		//        sht40x_interface_debug_print("\nDevice variant: %d\n", variant);
		//        sht40x_basic_get_addr((uint8_t *) & deviceAdd);
		//        sht40x_interface_debug_print("\nDevice Address: %x\n", deviceAdd);
		

	}
}

/**
 * @brief i2c data transmit
 * @param[in] addr is the slave address
 * @param[in] reg the register to write
 * @param[in] buf the data to be written
 * @param[in] len size of data
 * @return  status code
 * 			- 0 success
 * 			- 1 failed to write
 * @note	none
 * */
uint8_t i2c_write(uint8_t addr, uint8_t *pBuf, uint8_t len)
{
 	/* timeout is used to get out of twim_release, when there is no device connected to the bus*/
 	uint16_t              timeout = 10000;
	 
 	while (I2C_BUSY == I2C_0_open(addr) && --timeout)
 	; // sit here until we get the bus..
 	if (!timeout)
 	return I2C_BUSY;
	 
	 I2C_0_set_buffer((uint8_t *)pBuf, len);
	 // Start a Write operation
	 I2C_0_master_write();
	 timeout = 10000;
	 while (I2C_BUSY == I2C_0_close() && --timeout); // sit here until finished.
	 if (!timeout){
		return 1;
	}
  return 0;

}

/**
 * @brief i2c data Read
 * @param[in] addr is the slave address
 * @param[in] reg the register to read
 * @param[out] buf point to data to read
 * @param[in] len size of data
 * @return  status code
 * 			- 0 success
 * 			- 1 failed to read
 * @note	none
 * */

uint8_t i2c_read(uint8_t addr, uint8_t *pBuf, uint8_t len)
{
    /* timeout is used to get out of twim_release, when there is no device connected to the bus*/
    uint16_t              timeout = 10000;

    while (I2C_BUSY == I2C_0_open(addr) && --timeout)
    ; // sit here until we get the bus..
    if (!timeout)
    return I2C_BUSY;
     	
    I2C_0_set_buffer((uint8_t *)pBuf, len);
    // Start a Write operation
    I2C_0_master_read();
    timeout = 10000;
    while (I2C_BUSY == I2C_0_close() && --timeout); // sit here until finished.
    if (!timeout){
		return 1;
	}
	return 0;
}

void delay_ms(uint32_t u32Ms)
{
	while(u32Ms--)
	{
		_delay_ms(1);
	}

}

