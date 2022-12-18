################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mini_project_4.c \
../my_gpio.c \
../my_icu.c \
../my_lcd.c \
../my_ultrasonic.c 

OBJS += \
./mini_project_4.o \
./my_gpio.o \
./my_icu.o \
./my_lcd.o \
./my_ultrasonic.o 

C_DEPS += \
./mini_project_4.d \
./my_gpio.d \
./my_icu.d \
./my_lcd.d \
./my_ultrasonic.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


