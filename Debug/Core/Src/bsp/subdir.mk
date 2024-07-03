################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/bsp/flash.c \
../Core/Src/bsp/heap.c \
../Core/Src/bsp/led.c \
../Core/Src/bsp/mcu.c \
../Core/Src/bsp/nfc.c \
../Core/Src/bsp/sensor.c \
../Core/Src/bsp/sx1272.c 

OBJS += \
./Core/Src/bsp/flash.o \
./Core/Src/bsp/heap.o \
./Core/Src/bsp/led.o \
./Core/Src/bsp/mcu.o \
./Core/Src/bsp/nfc.o \
./Core/Src/bsp/sensor.o \
./Core/Src/bsp/sx1272.o 

C_DEPS += \
./Core/Src/bsp/flash.d \
./Core/Src/bsp/heap.d \
./Core/Src/bsp/led.d \
./Core/Src/bsp/mcu.d \
./Core/Src/bsp/nfc.d \
./Core/Src/bsp/sensor.d \
./Core/Src/bsp/sx1272.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/bsp/%.o Core/Src/bsp/%.su Core/Src/bsp/%.cyclo: ../Core/Src/bsp/%.c Core/Src/bsp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g -DDEBUG -DDEFAULT_WINDOW_SZ=16384 -DWOLFSSL_USER_SETTINGS -DUSE_HAL_DRIVER -DSTM32F205xx -c -I../Core/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/ -I../Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/ -I../wolfSSL -I../wolfSSH -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Drivers/ST25DV/Inc" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/bsp/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/common/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/socket/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/spi_flash/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/driver/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/littlefs" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-bsp

clean-Core-2f-Src-2f-bsp:
	-$(RM) ./Core/Src/bsp/flash.cyclo ./Core/Src/bsp/flash.d ./Core/Src/bsp/flash.o ./Core/Src/bsp/flash.su ./Core/Src/bsp/heap.cyclo ./Core/Src/bsp/heap.d ./Core/Src/bsp/heap.o ./Core/Src/bsp/heap.su ./Core/Src/bsp/led.cyclo ./Core/Src/bsp/led.d ./Core/Src/bsp/led.o ./Core/Src/bsp/led.su ./Core/Src/bsp/mcu.cyclo ./Core/Src/bsp/mcu.d ./Core/Src/bsp/mcu.o ./Core/Src/bsp/mcu.su ./Core/Src/bsp/nfc.cyclo ./Core/Src/bsp/nfc.d ./Core/Src/bsp/nfc.o ./Core/Src/bsp/nfc.su ./Core/Src/bsp/sensor.cyclo ./Core/Src/bsp/sensor.d ./Core/Src/bsp/sensor.o ./Core/Src/bsp/sensor.su ./Core/Src/bsp/sx1272.cyclo ./Core/Src/bsp/sx1272.d ./Core/Src/bsp/sx1272.o ./Core/Src/bsp/sx1272.su

.PHONY: clean-Core-2f-Src-2f-bsp

