################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Auditorium.cpp \
../src/Seat.cpp \
../src/SeatList.cpp \
../src/Theatre.cpp \
../src/Utilities.cpp \
../src/main.cpp 

OBJS += \
./src/Auditorium.o \
./src/Seat.o \
./src/SeatList.o \
./src/Theatre.o \
./src/Utilities.o \
./src/main.o 

CPP_DEPS += \
./src/Auditorium.d \
./src/Seat.d \
./src/SeatList.d \
./src/Theatre.d \
./src/Utilities.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


