################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USB_DEVICE/App/usb_device.c \
../USB_DEVICE/App/usbd_cdc_if.c \
../USB_DEVICE/App/usbd_desc.c 

OBJS += \
./USB_DEVICE/App/usb_device.o \
./USB_DEVICE/App/usbd_cdc_if.o \
./USB_DEVICE/App/usbd_desc.o 

C_DEPS += \
./USB_DEVICE/App/usb_device.d \
./USB_DEVICE/App/usbd_cdc_if.d \
./USB_DEVICE/App/usbd_desc.d 


# Each subdirectory must supply rules for building sources it contributes
USB_DEVICE/App/%.o USB_DEVICE/App/%.su USB_DEVICE/App/%.cyclo: ../USB_DEVICE/App/%.c USB_DEVICE/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g -DDEBUG -DDEFAULT_WINDOW_SZ=16384 -DWOLFSSL_USER_SETTINGS -DUSE_HAL_DRIVER -DSTM32F205xx -c -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Core/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/ -I../Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/ -I../wolfSSL -I../wolfSSH -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Drivers/ST25DV/Inc" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/bsp/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/common/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/socket/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/spi_flash/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/winc1500_19.6.1/driver/include" -I"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/Middlewares/Third_Party/littlefs" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-USB_DEVICE-2f-App

clean-USB_DEVICE-2f-App:
	-$(RM) ./USB_DEVICE/App/usb_device.cyclo ./USB_DEVICE/App/usb_device.d ./USB_DEVICE/App/usb_device.o ./USB_DEVICE/App/usb_device.su ./USB_DEVICE/App/usbd_cdc_if.cyclo ./USB_DEVICE/App/usbd_cdc_if.d ./USB_DEVICE/App/usbd_cdc_if.o ./USB_DEVICE/App/usbd_cdc_if.su ./USB_DEVICE/App/usbd_desc.cyclo ./USB_DEVICE/App/usbd_desc.d ./USB_DEVICE/App/usbd_desc.o ./USB_DEVICE/App/usbd_desc.su

.PHONY: clean-USB_DEVICE-2f-App

