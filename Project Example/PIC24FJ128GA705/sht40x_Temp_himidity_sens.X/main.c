/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.1
        Device            :  PIC24FJ128GA705
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.70
        MPLAB 	          :  MPLAB X v5.50
 */

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
 */

/**
  Section: Included Files
 */
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "sht40x_driver/sht40x_driver_basic.h"
#include "mcc_generated_files/i2c1.h"
#include "utilies_file.h"

/*
                         Main application
 */
sht40x_info_t sht40xInfo;         /**< structure info object definition */
sht40x_data_t dataRead;           /**< data read object definition */

int err;
uint32_t UID;
uint8_t variant;
uint8_t deviceAdd;
uint8_t NumberSamples = 10;

I2C1_MESSAGE_STATUS status;

uint8_t i2c_read(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);
uint8_t i2c_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);

int main(void) {
    // initialize the device
    SYSTEM_Initialize();

    sht40x_basic_initialize(SHT40_AD1B_VARIANT);
    sht40x_info(&sht40xInfo);

    sht40x_interface_debug_print("Chip Name: \t%s\r\n", sht40xInfo.chip_name);
    sht40x_interface_debug_print("Manufacturer: \t%s\r\n", sht40xInfo.manufacturer_name);
    sht40x_interface_debug_print("Interface Protocol: \t%s\r\n", sht40xInfo.interface);
    sht40x_interface_debug_print("Supply Volt Max: \t%.1f V\r\n", sht40xInfo.supply_voltage_max_v);
    sht40x_interface_debug_print("Supply Volt Min: \t%.1f V\r\n", sht40xInfo.supply_voltage_min_v);
    sht40x_interface_debug_print("Maximum Current: \t%.1f uA\r\n", sht40xInfo.max_current_ma);
    sht40x_interface_debug_print("Max Temperature: \t%.1f C\r\n", sht40xInfo.temperature_max);
    sht40x_interface_debug_print("Diver Version: \t\tV%.1f.%.2d\r\n", (sht40xInfo.driver_version / 1000), (uint8_t) (sht40xInfo.driver_version - (uint8_t) (sht40xInfo.driver_version / 100)*100));

    while (1) {
 
        delay_ms(3000);
        
		err =  sht40x_basic_get_temp_rh(SHT40X_PRECISION_HIGH, &dataRead);                               /**< Take temperature and humidity measurement */
		sht40x_interface_debug_print("\nTemp C: %.2f\n", dataRead.temperature_C);
		sht40x_interface_debug_print("Temp F: %.2f\n", dataRead.temperature_F);
		sht40x_interface_debug_print("Humidity: %.2f\n", dataRead.humidity);
		
		for(int index = 0; index < RESPONSE_LENGTH; index++){
			sht40x_interface_debug_print("raw data: 0x%.2x\n", dataRead.rawData[index]);
		}
		
		err = sht40x_basic_get_serial_number( (uint32_t*)&UID );                                         /**< Read sensor unique ID (Serial number) */
		sht40x_interface_debug_print("\nserial number : %lu\n", UID);
        
//
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

           // Add your application code
    }

    return 1;
}


uint8_t i2c_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len) {
    I2C1_MasterWrite((uint8_t *) & reg, 1, addr, &status);
    while (status == I2C1_MESSAGE_PENDING);

    if (status == I2C1_MESSAGE_FAIL) {
        return 1;
    }

    return 0; /**< success */
}

uint8_t i2c_read(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len) {

    I2C1_MasterRead((uint8_t *) buf, len, addr, &status);
    while (status == I2C1_MESSAGE_PENDING);

    if (status == I2C1_MESSAGE_FAIL) {
        return 1;
    }

    return 0; /**< success */
}

/**
 End of File
 */