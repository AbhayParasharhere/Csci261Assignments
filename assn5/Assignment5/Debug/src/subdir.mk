################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../src/fibonacci_dynamic.S \
../src/fibonacci_recursive.S \
../src/fibonacci_sequence.S \
../src/main.S \
../src/show_fibonacci_seq.S 

OBJS += \
./src/fibonacci_dynamic.o \
./src/fibonacci_recursive.o \
./src/fibonacci_sequence.o \
./src/main.o \
./src/show_fibonacci_seq.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Arm Assembler 6'
	armclang --target=aarch64-arm-none-eabi -mcpu=cortex-a53+nocrypto -g -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


