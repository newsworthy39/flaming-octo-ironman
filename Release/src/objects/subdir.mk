################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/objects/AnimatedRectangle.cpp \
../src/objects/LargeImagePanel.cpp \
../src/objects/Progressbar.cpp 

OBJS += \
./src/objects/AnimatedRectangle.o \
./src/objects/LargeImagePanel.o \
./src/objects/Progressbar.o 

CPP_DEPS += \
./src/objects/AnimatedRectangle.d \
./src/objects/LargeImagePanel.d \
./src/objects/Progressbar.d 


# Each subdirectory must supply rules for building sources it contributes
src/objects/%.o: ../src/objects/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -std=c++11 -I"/home/gandalf/workspace/flaming-octo-ironman/src" -O2 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


