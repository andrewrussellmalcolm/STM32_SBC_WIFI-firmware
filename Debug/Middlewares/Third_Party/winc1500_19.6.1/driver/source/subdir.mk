################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_hif.c \
../Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_ota.c \
../Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_periph.c \
../Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_ssl.c \
../Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_wifi.c \
../Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmasic.c \
../Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmbus.c \
../Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmdrv.c \
../Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmspi.c 

OBJS += \
./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_hif.o \
./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_ota.o \
./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_periph.o \
./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_ssl.o \
./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_wifi.o \
./Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmasic.o \
./Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmbus.o \
./Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmdrv.o \
./Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmspi.o 

C_DEPS += \
./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_hif.d \
./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_ota.d \
./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_periph.d \
./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_ssl.d \
./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_wifi.d \
./Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmasic.d \
./Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmbus.d \
./Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmdrv.d \
./Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmspi.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/winc1500_19.6.1/driver/source/%.o Middlewares/Third_Party/winc1500_19.6.1/driver/source/%.su Middlewares/Third_Party/winc1500_19.6.1/driver/source/%.cyclo: ../Middlewares/Third_Party/winc1500_19.6.1/driver/source/%.c Middlewares/Third_Party/winc1500_19.6.1/driver/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g -DDEBUG -DSTM32F205xx -DWOLFSSH_NO_ABORT -DWOLFSSH_USER_IO -DNO_UNITTEST_MAIN_DRIVER -DNO_APITEST_MAIN_DRIVER -DNO_TESTSUITE_MAIN_DRIVER -DWOLFSSH_USER_SETTINGS -DWOLFSSL_USER_SETTINGS -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/ -I../Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/ -I../wolfSSL -I../wolfSSH -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Drivers/ST25DV/Inc" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/bsp/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/common/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/socket/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/spi_flash/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/driver/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/littlefs" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-winc1500_19-2e-6-2e-1-2f-driver-2f-source

clean-Middlewares-2f-Third_Party-2f-winc1500_19-2e-6-2e-1-2f-driver-2f-source:
	-$(RM) ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_hif.cyclo ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_hif.d ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_hif.o ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_hif.su ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_ota.cyclo ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_ota.d ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_ota.o ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_ota.su ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_periph.cyclo ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_periph.d ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_periph.o ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_periph.su ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_ssl.cyclo ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_ssl.d ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_ssl.o ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_ssl.su ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_wifi.cyclo ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_wifi.d ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_wifi.o ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/m2m_wifi.su ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmasic.cyclo ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmasic.d ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmasic.o ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmasic.su ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmbus.cyclo ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmbus.d ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmbus.o ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmbus.su ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmdrv.cyclo ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmdrv.d ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmdrv.o ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmdrv.su ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmspi.cyclo ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmspi.d ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmspi.o ./Middlewares/Third_Party/winc1500_19.6.1/driver/source/nmspi.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-winc1500_19-2e-6-2e-1-2f-driver-2f-source

