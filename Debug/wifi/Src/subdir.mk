################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../wifi/Src/wifi.c 

OBJS += \
./wifi/Src/wifi.o 

C_DEPS += \
./wifi/Src/wifi.d 


# Each subdirectory must supply rules for building sources it contributes
wifi/Src/%.o wifi/Src/%.su wifi/Src/%.cyclo: ../wifi/Src/%.c wifi/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F205xx -c -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Core/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Drivers/CMSIS/Include -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/Trifle/wifi/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-wifi-2f-Src

clean-wifi-2f-Src:
	-$(RM) ./wifi/Src/wifi.cyclo ./wifi/Src/wifi.d ./wifi/Src/wifi.o ./wifi/Src/wifi.su

.PHONY: clean-wifi-2f-Src

