################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/examples/echoserver/echoserver.c 

OBJS += \
./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/examples/echoserver/echoserver.o 

C_DEPS += \
./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/examples/echoserver/echoserver.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/examples/echoserver/%.o Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/examples/echoserver/%.su Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/examples/echoserver/%.cyclo: ../Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/examples/echoserver/%.c Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/examples/echoserver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F205xx -DDEBUG -DWOLFSSH_NO_ABORT -DWOLFSSH_USER_IO -DNO_UNITTEST_MAIN_DRIVER -DNO_APITEST_MAIN_DRIVER -DNO_TESTSUITE_MAIN_DRIVER -DWOLFSSH_USER_SETTINGS -DWOLFSSH_IGNORE_FILE_WARN -DWOLFSSL_USER_SETTINGS -DUSE_HAL_DRIVER -UWOLFSSH_TEST_THREADING -c -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Core/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Drivers/CMSIS/Include -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/littlefs" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Drivers/ST25DV/Inc" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Core/winc1500_19.6.1/spi_flash/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Core/winc1500_19.6.1/socket/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Core/winc1500_19.6.1/common/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Core/winc1500_19.6.1/driver/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Core/winc1500_19.6.1/bsp/include" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/ -I../Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/ -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/wolfssh" -I../wolfSSL -I../wolfSSH -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-wolfSSL_wolfSSH_wolfSSH-2f-wolfssh-2f-examples-2f-echoserver

clean-Middlewares-2f-Third_Party-2f-wolfSSL_wolfSSH_wolfSSH-2f-wolfssh-2f-examples-2f-echoserver:
	-$(RM) ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/examples/echoserver/echoserver.cyclo ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/examples/echoserver/echoserver.d ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/examples/echoserver/echoserver.o ./Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/examples/echoserver/echoserver.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-wolfSSL_wolfSSH_wolfSSH-2f-wolfssh-2f-examples-2f-echoserver

