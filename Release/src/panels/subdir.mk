################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/panels/AnimatedRectangle.cpp \
../src/panels/LargeImagePanel.cpp \
../src/panels/LogPanel.cpp \
../src/panels/Progressbar.cpp \
../src/panels/SmallImagePanel.cpp \
../src/panels/VideoPanel.cpp 

OBJS += \
./src/panels/AnimatedRectangle.o \
./src/panels/LargeImagePanel.o \
./src/panels/LogPanel.o \
./src/panels/Progressbar.o \
./src/panels/SmallImagePanel.o \
./src/panels/VideoPanel.o 

CPP_DEPS += \
./src/panels/AnimatedRectangle.d \
./src/panels/LargeImagePanel.d \
./src/panels/LogPanel.d \
./src/panels/Progressbar.d \
./src/panels/SmallImagePanel.d \
./src/panels/VideoPanel.d 


# Each subdirectory must supply rules for building sources it contributes
src/panels/%.o: ../src/panels/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -std=c++11 -I"/home/gandalf/workspace/flaming-octo-ironman/src" -I"/home/gandalf/workspace/flaming-octo-ironman/libs/sfeMovie/include" -I"/home/gandalf/workspace/flaming-octo-ironman/libs/SFML-2.3/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


