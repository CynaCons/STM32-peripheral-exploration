################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32f407xx.s 

OBJS += \
./startup/startup_stm32f407xx.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/inc" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/STM32F4-Discovery" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/ili9341" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/ft6x06" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/exc7200" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/n25q512a" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/cs43l22" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/lis3dsh" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/n25q128a" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/lsm303dlhc" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/Common" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/s25fl512s" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/ampire480272" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/ampire640480" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/ov2640" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/l3gd20" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/wm8994" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/lis302dl" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/ili9325" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/otm8009a" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/ts3510" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/stmpe1600" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/mfxstm32l152" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/ls016b8uy" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/stmpe811" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/st7789h2" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/st7735" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/s5k5cag" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities/Components/n25q256a" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/Utilities" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/HAL_Driver/Inc" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/HAL_Driver/Inc/Legacy" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/CMSIS/device" -I"/home/cynako/Workspaces/ac6-workspace/STM32-peripherals-exploration/CMSIS/core" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


