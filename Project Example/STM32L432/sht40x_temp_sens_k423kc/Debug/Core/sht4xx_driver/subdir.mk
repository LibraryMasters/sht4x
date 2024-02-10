################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/sht4xx_driver/sht40x_driver.c \
../Core/sht4xx_driver/sht40x_driver_basic.c \
../Core/sht4xx_driver/sht40x_driver_interface.c 

OBJS += \
./Core/sht4xx_driver/sht40x_driver.o \
./Core/sht4xx_driver/sht40x_driver_basic.o \
./Core/sht4xx_driver/sht40x_driver_interface.o 

C_DEPS += \
./Core/sht4xx_driver/sht40x_driver.d \
./Core/sht4xx_driver/sht40x_driver_basic.d \
./Core/sht4xx_driver/sht40x_driver_interface.d 


# Each subdirectory must supply rules for building sources it contributes
Core/sht4xx_driver/%.o Core/sht4xx_driver/%.su: ../Core/sht4xx_driver/%.c Core/sht4xx_driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I"E:/Library Master/sht4x Tempearture and Humidity sensor/Project Example/STM32L432/sht40x_temp_sens_k423kc/Core/sht4xx_driver" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-sht4xx_driver

clean-Core-2f-sht4xx_driver:
	-$(RM) ./Core/sht4xx_driver/sht40x_driver.d ./Core/sht4xx_driver/sht40x_driver.o ./Core/sht4xx_driver/sht40x_driver.su ./Core/sht4xx_driver/sht40x_driver_basic.d ./Core/sht4xx_driver/sht40x_driver_basic.o ./Core/sht4xx_driver/sht40x_driver_basic.su ./Core/sht4xx_driver/sht40x_driver_interface.d ./Core/sht4xx_driver/sht40x_driver_interface.o ./Core/sht4xx_driver/sht40x_driver_interface.su

.PHONY: clean-Core-2f-sht4xx_driver

