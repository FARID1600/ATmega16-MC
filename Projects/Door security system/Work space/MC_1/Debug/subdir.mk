################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../func_main1.c \
../main1.c \
../my_gpio.c \
../my_keypad.c \
../my_lcd.c \
../my_timer.c \
../my_uart.c 

OBJS += \
./func_main1.o \
./main1.o \
./my_gpio.o \
./my_keypad.o \
./my_lcd.o \
./my_timer.o \
./my_uart.o 

C_DEPS += \
./func_main1.d \
./main1.d \
./my_gpio.d \
./my_keypad.d \
./my_lcd.d \
./my_timer.d \
./my_uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


