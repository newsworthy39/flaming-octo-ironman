################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../libs/SFML-2.2/share/SFML/examples/opengl/OpenGL.cpp 

OBJS += \
./libs/SFML-2.2/share/SFML/examples/opengl/OpenGL.o 

CPP_DEPS += \
./libs/SFML-2.2/share/SFML/examples/opengl/OpenGL.d 


# Each subdirectory must supply rules for building sources it contributes
libs/SFML-2.2/share/SFML/examples/opengl/%.o: ../libs/SFML-2.2/share/SFML/examples/opengl/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/home/gandalf/workspace/flaming-octo-ironman/src" -O2 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


