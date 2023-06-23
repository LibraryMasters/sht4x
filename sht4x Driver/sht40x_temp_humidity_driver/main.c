#include "sht40x_driver_basic.h"

sht40x_info_t sht40xInfo;
sht40x_data_t dataRead;

int err;
uint32_t UID;
uint8_t variant;
uint8_t deviceAdd;
uint8_t NumberSamples = 10;

int main()
{

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
    sht40x_interface_debug_print("\nRecommended MCU flash: \t%dkB\r\n",sht40xInfo.flash_size_min);
    sht40x_interface_debug_print("Recommended MCU RAM: \t%dkB\r\n",sht40xInfo.ram_size_min);

    err =  sht40x_basic_get_temp_rh(SHT40X_PRECISION_HIGH, &dataRead);
    if(err)
    {
      sht40x_interface_debug_print("failed to read\n");
    }
    sht40x_interface_debug_print("\nTemp C: %.2f\n", dataRead.temperature_C);
    sht40x_interface_debug_print("Temp F: %.2f\n", dataRead.temperature_F);
    sht40x_interface_debug_print("Humidity: %.2f\n", dataRead.humidity);

    for (int index = 0; index < RESPONSE_LENGTH; index++)
        sht40x_interface_debug_print("Raw data : %.2x\n", dataRead.rawData[index]);

    /**Measure Temp and humidity with n number of samples */
    err = sht40x_basic_get_temp_humidity_nSample(SHT40X_PRECISION_HIGH, &dataRead, NumberSamples);
    sht40x_interface_debug_print("\nTemp C sampled: %.2f\n", dataRead.temperature_C);
    sht40x_interface_debug_print("Humidity sampled: %.2f\n", dataRead.humidity);

    /** Get device unique ID */
    err = sht40x_basic_get_serial_number((uint32_t*) &UID);
    if(err)
    {
      /**< do something */
    }
    sht40x_interface_debug_print("serial number : %lu\n", UID);

    /** Activate heater and measure temperature */
    err = sht40x_basic_activate_heater(SHT40X_HEATER_POWER_20mW_100mS, &dataRead);
    sht40x_interface_debug_print("\nHeater Temp C: %.2f\n", dataRead.temperature_C);
    sht40x_interface_debug_print("Heater Temp F: %.2f\n", dataRead.temperature_F);
    sht40x_interface_debug_print("Heater Humidity: %.2f\n", dataRead.humidity);
    return 0;
}



