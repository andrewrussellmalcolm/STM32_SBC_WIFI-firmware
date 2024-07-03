################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/tcp/tcp.c \
../Core/Src/tcp/tcp_client.c \
../Core/Src/tcp/tcp_server.c 

OBJS += \
./Core/Src/tcp/tcp.o \
./Core/Src/tcp/tcp_client.o \
./Core/Src/tcp/tcp_server.o 

C_DEPS += \
./Core/Src/tcp/tcp.d \
./Core/Src/tcp/tcp_client.d \
./Core/Src/tcp/tcp_server.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/tcp/%.o Core/Src/tcp/%.su Core/Src/tcp/%.cyclo: ../Core/Src/tcp/%.c Core/Src/tcp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g -DDEBUG -DDEFAULT_WINDOW_SZ=16384 -DWOLFSSL_USER_SETTINGS -DUSE_HAL_DRIVER -DSTM32F205xx -c -I../Core/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/ -I../Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/ -I../wolfSSL -I../wolfSSH -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Drivers/ST25DV/Inc" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/bsp/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/common/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/socket/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/spi_flash/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/driver/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/littlefs" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-tcp

clean-Core-2f-Src-2f-tcp:
	-$(RM) ./Core/Src/tcp/tcp.cyclo ./Core/Src/tcp/tcp.d ./Core/Src/tcp/tcp.o ./Core/Src/tcp/tcp.su ./Core/Src/tcp/tcp_client.cyclo ./Core/Src/tcp/tcp_client.d ./Core/Src/tcp/tcp_client.o ./Core/Src/tcp/tcp_client.su ./Core/Src/tcp/tcp_server.cyclo ./Core/Src/tcp/tcp_server.d ./Core/Src/tcp/tcp_server.o ./Core/Src/tcp/tcp_server.su

.PHONY: clean-Core-2f-Src-2f-tcp

