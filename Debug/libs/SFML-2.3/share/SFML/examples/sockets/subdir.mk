################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../libs/SFML-2.3/share/SFML/examples/sockets/Sockets.cpp \
../libs/SFML-2.3/share/SFML/examples/sockets/TCP.cpp \
../libs/SFML-2.3/share/SFML/examples/sockets/UDP.cpp 

OBJS += \
./libs/SFML-2.3/share/SFML/examples/sockets/Sockets.o \
./libs/SFML-2.3/share/SFML/examples/sockets/TCP.o \
./libs/SFML-2.3/share/SFML/examples/sockets/UDP.o 

CPP_DEPS += \
./libs/SFML-2.3/share/SFML/examples/sockets/Sockets.d \
./libs/SFML-2.3/share/SFML/examples/sockets/TCP.d \
./libs/SFML-2.3/share/SFML/examples/sockets/UDP.d 


# Each subdirectory must supply rules for building sources it contributes
libs/SFML-2.3/share/SFML/examples/sockets/%.o: ../libs/SFML-2.3/share/SFML/examples/sockets/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -std=c++11 -D__DEBUG__ -I../flaming-octo-ironman/libs/SFML-2.2/include -I../flaming-octo-ironman/libs/json11 -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


