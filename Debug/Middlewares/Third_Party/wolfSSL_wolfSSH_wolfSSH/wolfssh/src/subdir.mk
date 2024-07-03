################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/agent.c \
../Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/certman.c \
../Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/internal.c \
../Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/io.c \
../Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/keygen.c \
../Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/log.c \
../Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/misc.c \
../Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/port.c \
../Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/ssh.c \
../Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/wolfscp.c \
../Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/wolfsftp.c \
../Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/wolfterm.c 

OBJS += \
./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/agent.o \
./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/certman.o \
./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/internal.o \
./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/io.o \
./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/keygen.o \
./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/log.o \
./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/misc.o \
./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/port.o \
./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/ssh.o \
./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/wolfscp.o \
./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/wolfsftp.o \
./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/wolfterm.o 

C_DEPS += \
./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/agent.d \
./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/certman.d \
./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/internal.d \
./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/io.d \
./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/keygen.d \
./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/log.d \
./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/misc.d \
./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/port.d \
./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/ssh.d \
./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/wolfscp.d \
./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/wolfsftp.d \
./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/wolfterm.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/%.o Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/%.su Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/%.cyclo: ../Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/%.c Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g -DSTM32F205xx -DDEFAULT_MAX_PACKET_SZ=4096 -DDEFAULT_WINDOW_SZ=16384 -DDEBUG -DWOLFSSH_NO_ABORT -DWOLFSSH_USER_IO -DNO_UNITTEST_MAIN_DRIVER -DNO_APITEST_MAIN_DRIVER -DNO_TESTSUITE_MAIN_DRIVER -DWOLFSSH_USER_SETTINGS -DWOLFSSH_IGNORE_FILE_WARN -DWOLFSSL_USER_SETTINGS -DUSE_HAL_DRIVER -UWOLFSSH_TEST_THREADING -c -I../Core/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/ -I../Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/ -I../wolfSSL -I../wolfSSH -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Drivers/ST25DV/Inc" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/bsp/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/common/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/socket/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/spi_flash/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/driver/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/littlefs" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/log.o: ../Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/log.c Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g -DSTM32F205xx -DDEBUG_WOLFSSH -DDEBUG -DWOLFSSH_NO_ABORT -DWOLFSSH_USER_IO -DNO_UNITTEST_MAIN_DRIVER -DNO_APITEST_MAIN_DRIVER -DNO_TESTSUITE_MAIN_DRIVER -DWOLFSSH_USER_SETTINGS -DWOLFSSH_IGNORE_FILE_WARN -DWOLFSSL_USER_SETTINGS -DUSE_HAL_DRIVER -UWOLFSSH_TEST_THREADING -c -I../Core/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/ -I../Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/ -I../wolfSSL -I../wolfSSH -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Drivers/ST25DV/Inc" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/bsp/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/common/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/socket/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/spi_flash/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/driver/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/littlefs" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-wolfSSL_wolfSSH_wolfSSH-2f-wolfssh-2f-src

clean-Middlewares-2f-Third_Party-2f-wolfSSL_wolfSSH_wolfSSH-2f-wolfssh-2f-src:
	-$(RM) ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/agent.cyclo ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/agent.d ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/agent.o ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/agent.su ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/certman.cyclo ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/certman.d ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/certman.o ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/certman.su ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/internal.cyclo ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/internal.d ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/internal.o ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/internal.su ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/io.cyclo ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/io.d ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/io.o ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/io.su ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/keygen.cyclo ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/keygen.d ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/keygen.o ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/keygen.su ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/log.cyclo ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/log.d ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/log.o ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/log.su ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/misc.cyclo ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/misc.d ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/misc.o ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/misc.su ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/port.cyclo ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/port.d ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/port.o ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/port.su ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/ssh.cyclo ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/ssh.d ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/ssh.o ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/ssh.su ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/wolfscp.cyclo ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/wolfscp.d ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/wolfscp.o ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/wolfscp.su ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/wolfsftp.cyclo ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/wolfsftp.d ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/wolfsftp.o ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/wolfsftp.su ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/wolfterm.cyclo ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/wolfterm.d ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/wolfterm.o ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/wolfterm.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-wolfSSL_wolfSSH_wolfSSH-2f-wolfssh-2f-src

