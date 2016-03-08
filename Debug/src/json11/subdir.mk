################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/json11/json11.cpp 

OBJS += \
./src/json11/json11.o 

CPP_DEPS += \
./src/json11/json11.d 


# Each subdirectory must supply rules for building sources it contributes
src/json11/%.o: ../src/json11/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -std=c++11 -D__DEBUG__ -I"/home/gandalf/workspace/flaming-octo-ironman/src" -I"/home/gandalf/workspace/flaming-octo-ironman/libs/SFML-2.3/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


