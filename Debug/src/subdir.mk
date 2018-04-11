################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/delay.c \
../src/gpio.c \
../src/ibutton.c \
../src/main.c \
../src/oneWire.c \
../src/syscalls.c \
../src/system_stm32f0xx.c \
../src/usart.c 

OBJS += \
./src/delay.o \
./src/gpio.o \
./src/ibutton.o \
./src/main.o \
./src/oneWire.o \
./src/syscalls.o \
./src/system_stm32f0xx.o \
./src/usart.o 

C_DEPS += \
./src/delay.d \
./src/gpio.d \
./src/ibutton.d \
./src/main.d \
./src/oneWire.d \
./src/syscalls.d \
./src/system_stm32f0xx.d \
./src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32F0 -DSTM32F042K6Tx -DNUCLEO_F042K6 -DDEBUG -DSTM32F042 -DUSE_STDPERIPH_DRIVER -I"/home/mateus/workspace/my_project/CPAL_Driver/inc" -I"/home/mateus/workspace/my_project/StdPeriph_Driver/inc" -I"/home/mateus/workspace/my_project/inc" -I"/home/mateus/workspace/my_project/CMSIS/device" -I"/home/mateus/workspace/my_project/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


