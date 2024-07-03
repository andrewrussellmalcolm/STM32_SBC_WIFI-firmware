################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/ST25DV/Src/st25dv.c \
../Drivers/ST25DV/Src/st25dv_reg.c 

OBJS += \
./Drivers/ST25DV/Src/st25dv.o \
./Drivers/ST25DV/Src/st25dv_reg.o 

C_DEPS += \
./Drivers/ST25DV/Src/st25dv.d \
./Drivers/ST25DV/Src/st25dv_reg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/ST25DV/Src/%.o Drivers/ST25DV/Src/%.su Drivers/ST25DV/Src/%.cyclo: ../Drivers/ST25DV/Src/%.c Drivers/ST25DV/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g -DDEBUG -DDEFAULT_WINDOW_SZ=16384 -DWOLFSSL_USER_SETTINGS -DUSE_HAL_DRIVER -DSTM32F205xx -c -I../Core/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/ -I../Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/ -I../wolfSSL -I../wolfSSH -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Drivers/ST25DV/Inc" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/bsp/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/common/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/socket/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/spi_flash/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/driver/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/littlefs" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-ST25DV-2f-Src

clean-Drivers-2f-ST25DV-2f-Src:
	-$(RM) ./Drivers/ST25DV/Src/st25dv.cyclo ./Drivers/ST25DV/Src/st25dv.d ./Drivers/ST25DV/Src/st25dv.o ./Drivers/ST25DV/Src/st25dv.su ./Drivers/ST25DV/Src/st25dv_reg.cyclo ./Drivers/ST25DV/Src/st25dv_reg.d ./Drivers/ST25DV/Src/st25dv_reg.o ./Drivers/ST25DV/Src/st25dv_reg.su

.PHONY: clean-Drivers-2f-ST25DV-2f-Src

