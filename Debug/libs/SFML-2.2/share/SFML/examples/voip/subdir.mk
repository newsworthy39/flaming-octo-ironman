################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../libs/SFML-2.2/share/SFML/examples/voip/Client.cpp \
../libs/SFML-2.2/share/SFML/examples/voip/Server.cpp \
../libs/SFML-2.2/share/SFML/examples/voip/VoIP.cpp 

OBJS += \
./libs/SFML-2.2/share/SFML/examples/voip/Client.o \
./libs/SFML-2.2/share/SFML/examples/voip/Server.o \
./libs/SFML-2.2/share/SFML/examples/voip/VoIP.o 

CPP_DEPS += \
./libs/SFML-2.2/share/SFML/examples/voip/Client.d \
./libs/SFML-2.2/share/SFML/examples/voip/Server.d \
./libs/SFML-2.2/share/SFML/examples/voip/VoIP.d 


# Each subdirectory must supply rules for building sources it contributes
libs/SFML-2.2/share/SFML/examples/voip/%.o: ../libs/SFML-2.2/share/SFML/examples/voip/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -std=c++11 -D__DEBUG__ -I../flaming-octo-ironman/libs/SFML-2.2/include -I../flaming-octo-ironman/libs/json11 -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

