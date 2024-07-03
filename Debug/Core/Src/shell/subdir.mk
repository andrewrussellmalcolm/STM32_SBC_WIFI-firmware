################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/shell/echo_server.c \
../Core/Src/shell/shell.c \
../Core/Src/shell/shell_clock.c \
../Core/Src/shell/shell_flash.c \
../Core/Src/shell/shell_fs.c \
../Core/Src/shell/shell_gpio.c \
../Core/Src/shell/shell_led.c \
../Core/Src/shell/shell_lora.c \
../Core/Src/shell/shell_nfc.c \
../Core/Src/shell/shell_sensor.c \
../Core/Src/shell/shell_serial.c \
../Core/Src/shell/shell_server.c \
../Core/Src/shell/shell_sys.c \
../Core/Src/shell/shell_tcp.c \
../Core/Src/shell/shell_timer.c \
../Core/Src/shell/shell_wifi.c \
../Core/Src/shell/ssh_server.c \
../Core/Src/shell/ssh_server_utils.c \
../Core/Src/shell/upload_server.c 

OBJS += \
./Core/Src/shell/echo_server.o \
./Core/Src/shell/shell.o \
./Core/Src/shell/shell_clock.o \
./Core/Src/shell/shell_flash.o \
./Core/Src/shell/shell_fs.o \
./Core/Src/shell/shell_gpio.o \
./Core/Src/shell/shell_led.o \
./Core/Src/shell/shell_lora.o \
./Core/Src/shell/shell_nfc.o \
./Core/Src/shell/shell_sensor.o \
./Core/Src/shell/shell_serial.o \
./Core/Src/shell/shell_server.o \
./Core/Src/shell/shell_sys.o \
./Core/Src/shell/shell_tcp.o \
./Core/Src/shell/shell_timer.o \
./Core/Src/shell/shell_wifi.o \
./Core/Src/shell/ssh_server.o \
./Core/Src/shell/ssh_server_utils.o \
./Core/Src/shell/upload_server.o 

C_DEPS += \
./Core/Src/shell/echo_server.d \
./Core/Src/shell/shell.d \
./Core/Src/shell/shell_clock.d \
./Core/Src/shell/shell_flash.d \
./Core/Src/shell/shell_fs.d \
./Core/Src/shell/shell_gpio.d \
./Core/Src/shell/shell_led.d \
./Core/Src/shell/shell_lora.d \
./Core/Src/shell/shell_nfc.d \
./Core/Src/shell/shell_sensor.d \
./Core/Src/shell/shell_serial.d \
./Core/Src/shell/shell_server.d \
./Core/Src/shell/shell_sys.d \
./Core/Src/shell/shell_tcp.d \
./Core/Src/shell/shell_timer.d \
./Core/Src/shell/shell_wifi.d \
./Core/Src/shell/ssh_server.d \
./Core/Src/shell/ssh_server_utils.d \
./Core/Src/shell/upload_server.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/shell/%.o Core/Src/shell/%.su Core/Src/shell/%.cyclo: ../Core/Src/shell/%.c Core/Src/shell/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g -DDEBUG -DDEFAULT_WINDOW_SZ=16384 -DWOLFSSL_USER_SETTINGS -DUSE_HAL_DRIVER -DSTM32F205xx -c -I../Core/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/ -I../Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/ -I../wolfSSL -I../wolfSSH -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Drivers/ST25DV/Inc" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/bsp/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/common/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/socket/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/spi_flash/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/driver/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/littlefs" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-shell

clean-Core-2f-Src-2f-shell:
	-$(RM) ./Core/Src/shell/echo_server.cyclo ./Core/Src/shell/echo_server.d ./Core/Src/shell/echo_server.o ./Core/Src/shell/echo_server.su ./Core/Src/shell/shell.cyclo ./Core/Src/shell/shell.d ./Core/Src/shell/shell.o ./Core/Src/shell/shell.su ./Core/Src/shell/shell_clock.cyclo ./Core/Src/shell/shell_clock.d ./Core/Src/shell/shell_clock.o ./Core/Src/shell/shell_clock.su ./Core/Src/shell/shell_flash.cyclo ./Core/Src/shell/shell_flash.d ./Core/Src/shell/shell_flash.o ./Core/Src/shell/shell_flash.su ./Core/Src/shell/shell_fs.cyclo ./Core/Src/shell/shell_fs.d ./Core/Src/shell/shell_fs.o ./Core/Src/shell/shell_fs.su ./Core/Src/shell/shell_gpio.cyclo ./Core/Src/shell/shell_gpio.d ./Core/Src/shell/shell_gpio.o ./Core/Src/shell/shell_gpio.su ./Core/Src/shell/shell_led.cyclo ./Core/Src/shell/shell_led.d ./Core/Src/shell/shell_led.o ./Core/Src/shell/shell_led.su ./Core/Src/shell/shell_lora.cyclo ./Core/Src/shell/shell_lora.d ./Core/Src/shell/shell_lora.o ./Core/Src/shell/shell_lora.su ./Core/Src/shell/shell_nfc.cyclo ./Core/Src/shell/shell_nfc.d ./Core/Src/shell/shell_nfc.o ./Core/Src/shell/shell_nfc.su ./Core/Src/shell/shell_sensor.cyclo ./Core/Src/shell/shell_sensor.d ./Core/Src/shell/shell_sensor.o ./Core/Src/shell/shell_sensor.su ./Core/Src/shell/shell_serial.cyclo ./Core/Src/shell/shell_serial.d ./Core/Src/shell/shell_serial.o ./Core/Src/shell/shell_serial.su ./Core/Src/shell/shell_server.cyclo ./Core/Src/shell/shell_server.d ./Core/Src/shell/shell_server.o ./Core/Src/shell/shell_server.su ./Core/Src/shell/shell_sys.cyclo ./Core/Src/shell/shell_sys.d ./Core/Src/shell/shell_sys.o ./Core/Src/shell/shell_sys.su ./Core/Src/shell/shell_tcp.cyclo ./Core/Src/shell/shell_tcp.d ./Core/Src/shell/shell_tcp.o ./Core/Src/shell/shell_tcp.su ./Core/Src/shell/shell_timer.cyclo ./Core/Src/shell/shell_timer.d ./Core/Src/shell/shell_timer.o ./Core/Src/shell/shell_timer.su ./Core/Src/shell/shell_wifi.cyclo ./Core/Src/shell/shell_wifi.d ./Core/Src/shell/shell_wifi.o ./Core/Src/shell/shell_wifi.su ./Core/Src/shell/ssh_server.cyclo ./Core/Src/shell/ssh_server.d ./Core/Src/shell/ssh_server.o ./Core/Src/shell/ssh_server.su ./Core/Src/shell/ssh_server_utils.cyclo ./Core/Src/shell/ssh_server_utils.d ./Core/Src/shell/ssh_server_utils.o ./Core/Src/shell/ssh_server_utils.su ./Core/Src/shell/upload_server.cyclo ./Core/Src/shell/upload_server.d ./Core/Src/shell/upload_server.o ./Core/Src/shell/upload_server.su

.PHONY: clean-Core-2f-Src-2f-shell

