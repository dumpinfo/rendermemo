################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Images/blast.c \
../src/Images/bomb.c \
../src/Images/dot.c \
../src/Images/eight.c \
../src/Images/five.c \
../src/Images/flag.c \
../src/Images/flagsTxt.c \
../src/Images/four.c \
../src/Images/gameOver.c \
../src/Images/happy.c \
../src/Images/instruction.c \
../src/Images/new.c \
../src/Images/nine.c \
../src/Images/num1.c \
../src/Images/num2.c \
../src/Images/num3.c \
../src/Images/num4.c \
../src/Images/num5.c \
../src/Images/num6.c \
../src/Images/num7.c \
../src/Images/num8.c \
../src/Images/one.c \
../src/Images/open.c \
../src/Images/sad.c \
../src/Images/scoreTxt.c \
../src/Images/seven.c \
../src/Images/six.c \
../src/Images/slash.c \
../src/Images/three.c \
../src/Images/two.c \
../src/Images/win.c \
../src/Images/zero.c 

OBJS += \
./src/Images/blast.o \
./src/Images/bomb.o \
./src/Images/dot.o \
./src/Images/eight.o \
./src/Images/five.o \
./src/Images/flag.o \
./src/Images/flagsTxt.o \
./src/Images/four.o \
./src/Images/gameOver.o \
./src/Images/happy.o \
./src/Images/instruction.o \
./src/Images/new.o \
./src/Images/nine.o \
./src/Images/num1.o \
./src/Images/num2.o \
./src/Images/num3.o \
./src/Images/num4.o \
./src/Images/num5.o \
./src/Images/num6.o \
./src/Images/num7.o \
./src/Images/num8.o \
./src/Images/one.o \
./src/Images/open.o \
./src/Images/sad.o \
./src/Images/scoreTxt.o \
./src/Images/seven.o \
./src/Images/six.o \
./src/Images/slash.o \
./src/Images/three.o \
./src/Images/two.o \
./src/Images/win.o \
./src/Images/zero.o 

C_DEPS += \
./src/Images/blast.d \
./src/Images/bomb.d \
./src/Images/dot.d \
./src/Images/eight.d \
./src/Images/five.d \
./src/Images/flag.d \
./src/Images/flagsTxt.d \
./src/Images/four.d \
./src/Images/gameOver.d \
./src/Images/happy.d \
./src/Images/instruction.d \
./src/Images/new.d \
./src/Images/nine.d \
./src/Images/num1.d \
./src/Images/num2.d \
./src/Images/num3.d \
./src/Images/num4.d \
./src/Images/num5.d \
./src/Images/num6.d \
./src/Images/num7.d \
./src/Images/num8.d \
./src/Images/one.d \
./src/Images/open.d \
./src/Images/sad.d \
./src/Images/scoreTxt.d \
./src/Images/seven.d \
./src/Images/six.d \
./src/Images/slash.d \
./src/Images/three.d \
./src/Images/two.d \
./src/Images/win.d \
./src/Images/zero.d 


# Each subdirectory must supply rules for building sources it contributes
src/Images/%.o: ../src/Images/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


