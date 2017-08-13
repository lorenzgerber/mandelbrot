################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ComplexZ.cpp \
../src/Fractal.cpp \
../src/main.cpp \
../src/mandelbrot.cpp 

OBJS += \
./src/ComplexZ.o \
./src/Fractal.o \
./src/main.o \
./src/mandelbrot.o 

CPP_DEPS += \
./src/ComplexZ.d \
./src/Fractal.d \
./src/main.d \
./src/mandelbrot.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++  `pkg-config --cflags gtk+-2.0` -I/usr/include/gtk-2.0/ -I/usr/include/x86_64-linux-gnu -I/usr/local/include -I/usr/include/glib-2.0 -I/usr/include -include/usr/include/glib-2.0/glib.h -O0 -Ofast -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


