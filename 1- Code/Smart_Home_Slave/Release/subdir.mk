################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CLCD_program.c \
../DIO_program.c \
../EEPROM_program.c \
../GIE_program.c \
../KPD_program.c \
../MAP_program.c \
../SPI_program.c \
../SvM_program.c \
../TIMER_program.c \
../main.c 

OBJS += \
./CLCD_program.o \
./DIO_program.o \
./EEPROM_program.o \
./GIE_program.o \
./KPD_program.o \
./MAP_program.o \
./SPI_program.o \
./SvM_program.o \
./TIMER_program.o \
./main.o 

C_DEPS += \
./CLCD_program.d \
./DIO_program.d \
./EEPROM_program.d \
./GIE_program.d \
./KPD_program.d \
./MAP_program.d \
./SPI_program.d \
./SvM_program.d \
./TIMER_program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


