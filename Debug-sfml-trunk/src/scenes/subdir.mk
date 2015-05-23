################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/scenes/Dashboard.cpp 

OBJS += \
./src/scenes/Dashboard.o 

CPP_DEPS += \
./src/scenes/Dashboard.d 


# Each subdirectory must supply rules for building sources it contributes
src/scenes/%.o: ../src/scenes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -std=c++11 -D__DEBUG__ -I"/home/gandalf/workspace/flaming-octo-ironman/src" -I"/home/gandalf/workspace/flaming-octo-ironman/libs/sfeMovie/include" -I"/home/gandalf/workspace/flaming-octo-ironman/libs/SFML-trunk/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


