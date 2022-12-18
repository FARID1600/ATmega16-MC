################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../eeprom.c \
../func_main2.c \
../main2.c \
../my_gpio.c \
../my_i2c.c \
../my_motor.c \
../my_timer.c \
../my_uart.c 

OBJS += \
./eeprom.o \
./func_main2.o \
./main2.o \
./my_gpio.o \
./my_i2c.o \
./my_motor.o \
./my_timer.o \
./my_uart.o 

C_DEPS += \
./eeprom.d \
./func_main2.d \
./main2.d \
./my_gpio.d \
./my_i2c.d \
./my_motor.d \
./my_timer.d \
./my_uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


