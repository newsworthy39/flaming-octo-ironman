################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AnimatedRectangle.cpp \
../src/Bardiagrams.cpp \
../src/JSONThreadedPoller.cpp \
../src/flaming-octo-ironman.cpp 

OBJS += \
./src/AnimatedRectangle.o \
./src/Bardiagrams.o \
./src/JSONThreadedPoller.o \
./src/flaming-octo-ironman.o 

CPP_DEPS += \
./src/AnimatedRectangle.d \
./src/Bardiagrams.d \
./src/JSONThreadedPoller.d \
./src/flaming-octo-ironman.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -D__DEBUG__ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


