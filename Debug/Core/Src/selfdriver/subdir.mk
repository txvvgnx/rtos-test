################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/selfdriver/bme280.c 

OBJS += \
./Core/Src/selfdriver/bme280.o 

C_DEPS += \
./Core/Src/selfdriver/bme280.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/selfdriver/%.o Core/Src/selfdriver/%.su Core/Src/selfdriver/%.cyclo: ../Core/Src/selfdriver/%.c Core/Src/selfdriver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-selfdriver

clean-Core-2f-Src-2f-selfdriver:
	-$(RM) ./Core/Src/selfdriver/bme280.cyclo ./Core/Src/selfdriver/bme280.d ./Core/Src/selfdriver/bme280.o ./Core/Src/selfdriver/bme280.su

.PHONY: clean-Core-2f-Src-2f-selfdriver

