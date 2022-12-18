################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lm35_sensor.c \
../my_adc.c \
../my_gpio.c \
../my_lcd.c \
../my_motor.c \
../project_part1.c \
../pwm.c 

OBJS += \
./lm35_sensor.o \
./my_adc.o \
./my_gpio.o \
./my_lcd.o \
./my_motor.o \
./project_part1.o \
./pwm.o 

C_DEPS += \
./lm35_sensor.d \
./my_adc.d \
./my_gpio.d \
./my_lcd.d \
./my_motor.d \
./project_part1.d \
./pwm.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


