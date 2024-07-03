################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/test/subdir.mk
-include Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/port/st/subdir.mk
-include Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/port/atmel/subdir.mk
-include Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/port/arm/subdir.mk
-include Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/subdir.mk
-include Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/benchmark/subdir.mk
-include Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/subdir.mk
-include Middlewares/Third_Party/wolfSSL_wolfSSH_wolfSSH/wolfssh/src/subdir.mk
-include Middlewares/Third_Party/winc1500_19.6.1/spi_flash/source/subdir.mk
-include Middlewares/Third_Party/winc1500_19.6.1/socket/source/subdir.mk
-include Middlewares/Third_Party/winc1500_19.6.1/driver/source/subdir.mk
-include Middlewares/Third_Party/winc1500_19.6.1/common/source/subdir.mk
-include Middlewares/Third_Party/winc1500_19.6.1/bsp/source/subdir.mk
-include Middlewares/Third_Party/littlefs/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include Drivers/STM32F2xx_HAL_Driver/Src/subdir.mk
-include Drivers/ST25DV/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/tcp/subdir.mk
-include Core/Src/tasks/subdir.mk
-include Core/Src/shell/subdir.mk
-include Core/Src/ffs/subdir.mk
-include Core/Src/bsp/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := STM32_SBC_WIFI
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
STM32_SBC_WIFI.elf \

MAP_FILES += \
STM32_SBC_WIFI.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
STM32_SBC_WIFI.list \


# All Target
all: main-build

# Main-build Target
main-build: STM32_SBC_WIFI.elf secondary-outputs

# Tool invocations
STM32_SBC_WIFI.elf STM32_SBC_WIFI.map: $(OBJS) $(USER_OBJS) /home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/STM32F205RGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "STM32_SBC_WIFI.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"/home/andrew/STM32CubeIDE/workspace_1.6.0/STM32_SBC_WIFI/STM32F205RGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="STM32_SBC_WIFI.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

STM32_SBC_WIFI.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "STM32_SBC_WIFI.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) STM32_SBC_WIFI.elf STM32_SBC_WIFI.list STM32_SBC_WIFI.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
