################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../libs/json11/json11.cpp 

OBJS += \
./libs/json11/json11.o 

CPP_DEPS += \
./libs/json11/json11.d 


# Each subdirectory must supply rules for building sources it contributes
libs/json11/%.o: ../libs/json11/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -std=c++11 -D__DEBUG__ -I../flaming-octo-ironman/libs/SFML-2.2/include -I../flaming-octo-ironman/libs/json11 -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


