#include <atmel_start.h>
#include <util/delay.h>
#include "sht40x_driver_basic.h"

sht40x_info_t sht40xInfo;
sht40x_data_t dataRead;

int err;
uint32_t UID;
uint8_t variant;
uint8_t deviceAdd;

uint8_t i2c_read_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);
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
		
		err =  sht40x_basic_get_temp_rh(SHT40X_PRECISION_HIGH, &dataRead);
		sht40x_interface_debug_print("\nTemp C: %.2f\n", dataRead.temperature_C);
		sht40x_interface_debug_print("Temp F: %.2f\n", dataRead.temperature_F);
		sht40x_interface_debug_print("Humidity: %.2f\n", dataRead.humidity);

		err = sht40x_basic_get_serial_number( (uint32_t*)&UID );
		sht40x_interface_debug_print("\nserial number : %lu\n", UID);
		
// 		err = sht40x_basic_activate_heater(SHT40X_HEATER_POWER_200mW_100mS, &dataRead);
// 		sht40x_interface_debug_print("\nHeater Temp C: %.2f\n", dataRead.temperature_C);
// 		sht40x_interface_debug_print("Heater Temp F: %.2f\n", dataRead.temperature_F);
// 		sht40x_interface_debug_print("Heater Humidity: %.2f\n", dataRead.humidity);
		
		//sht40x_basic_get_variant((uint8_t *)&variant);
		//sht40x_interface_debug_print("\nDevice variant: %d\n", variant);
		//sht40x_basic_get_addr((uint8_t *)&deviceAdd);
		//sht40x_interface_debug_print("\nDevice Address: %x\n", deviceAdd);
		

	}
}


void delay_ms(uint32_t u32Ms)
{
	while(u32Ms)
	{
		_delay_ms(1);
		u32Ms--;
	}

}

uint8_t i2c_read_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
	I2C_0_do_transfer(reg, (uint32_t *)buf, len);
	return 0;
}

