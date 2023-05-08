#include <atmel_start.h>
#include "sht40x_driver_basic.h"

sht40x_info_t sht40xInfo;
sht40x_data_t dataRead;

int err;
uint32_t UID;
uint8_t variant;
uint8_t deviceAdd;

uint8_t i2c_read_data(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);

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
		gpio_toggle_pin_level(LED_GREEN);
		sht40x_interface_delay_ms(2000);
		
	  err =  sht40x_basic_get_temp_rh(SHT40X_PRECISION_HIGH, &dataRead);
	  sht40x_interface_debug_print("Temp C: %.2d\r", (int)dataRead.temperature_C);
	  sht40x_interface_debug_print("Temp F: %.2d\r", (int)dataRead.temperature_F);
	  sht40x_interface_debug_print("Humidity: %.2f\n", dataRead.humidity);

	  err = sht40x_basic_get_serial_number((uint32_t*) &UID);
	  sht40x_interface_debug_print("serial number : %lu\r", UID);
		
	}
}


void serial_print(char *const pBuffer, uint8_t u8Length)
{
	struct io_descriptor *io;

	//usart_async_register_callback(&USART_0, USART_ASYNC_TXC_CB, tx_cb_USART_0);
	/*usart_async_register_callback(&USART_0, USART_ASYNC_RXC_CB, rx_cb);
	usart_async_register_callback(&USART_0, USART_ASYNC_ERROR_CB, err_cb);*/
	usart_async_get_io_descriptor(&USART_0, &io);
	usart_async_enable(&USART_0);

	io_write(io, (uint8_t*)pBuffer, u8Length);
	
}

uint8_t i2c_read_data(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
		struct io_descriptor *I2C_0_io;

		i2c_m_sync_get_io_descriptor(&I2C_0, &I2C_0_io);
		i2c_m_sync_enable(&I2C_0);
		i2c_m_sync_set_slaveaddr(&I2C_0, addr, I2C_M_SEVEN);
		
		io_write(I2C_0_io, (uint8_t *)&reg, 1);
		sht40x_interface_delay_ms(15);
		io_read(I2C_0_io, buf,  len);
	return 0;
}

uint8_t i2c_write_data(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{

	return 0;	
}