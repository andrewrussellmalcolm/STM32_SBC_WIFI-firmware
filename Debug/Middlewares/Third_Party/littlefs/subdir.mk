################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/littlefs/lfs.c \
../Middlewares/Third_Party/littlefs/lfs_util.c 

OBJS += \
./Middlewares/Third_Party/littlefs/lfs.o \
./Middlewares/Third_Party/littlefs/lfs_util.o 

C_DEPS += \
./Middlewares/Third_Party/littlefs/lfs.d \
./Middlewares/Third_Party/littlefs/lfs_util.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/littlefs/%.o Middlewares/Third_Party/littlefs/%.su Middlewares/Third_Party/littlefs/%.cyclo: ../Middlewares/Third_Party/littlefs/%.c Middlewares/Third_Party/littlefs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g -DDEBUG -DWOLFSSH_NO_ABORT -DWOLFSSH_USER_IO -DNO_UNITTEST_MAIN_DRIVER -DNO_APITEST_MAIN_DRIVER -DNO_TESTSUITE_MAIN_DRIVER -DWOLFSSH_USER_SETTINGS -DWOLFSSL_USER_SETTINGS -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/ -I../Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/ -I../wolfSSL -I../wolfSSH -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Drivers/ST25DV/Inc" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/bsp/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/common/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/socket/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/spi_flash/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/driver/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/littlefs" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-littlefs

clean-Middlewares-2f-Third_Party-2f-littlefs:
	-$(RM) ./Middlewares/Third_Party/littlefs/lfs.cyclo ./Middlewares/Third_Party/littlefs/lfs.d ./Middlewares/Third_Party/littlefs/lfs.o ./Middlewares/Third_Party/littlefs/lfs.su ./Middlewares/Third_Party/littlefs/lfs_util.cyclo ./Middlewares/Third_Party/littlefs/lfs_util.d ./Middlewares/Third_Party/littlefs/lfs_util.o ./Middlewares/Third_Party/littlefs/lfs_util.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-littlefs
