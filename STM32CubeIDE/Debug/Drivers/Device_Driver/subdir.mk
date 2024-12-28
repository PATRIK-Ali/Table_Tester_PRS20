################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Device_Driver/GUI.c \
../Drivers/Device_Driver/RS485.c \
../Drivers/Device_Driver/SPI.c \
../Drivers/Device_Driver/delay.c \
../Drivers/Device_Driver/lcd.c \
../Drivers/Device_Driver/xpt2046.c 

OBJS += \
./Drivers/Device_Driver/GUI.o \
./Drivers/Device_Driver/RS485.o \
./Drivers/Device_Driver/SPI.o \
./Drivers/Device_Driver/delay.o \
./Drivers/Device_Driver/lcd.o \
./Drivers/Device_Driver/xpt2046.o 

C_DEPS += \
./Drivers/Device_Driver/GUI.d \
./Drivers/Device_Driver/RS485.d \
./Drivers/Device_Driver/SPI.d \
./Drivers/Device_Driver/delay.d \
./Drivers/Device_Driver/lcd.d \
./Drivers/Device_Driver/xpt2046.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Device_Driver/%.o Drivers/Device_Driver/%.su Drivers/Device_Driver/%.cyclo: ../Drivers/Device_Driver/%.c Drivers/Device_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DSTM32H573xx -DHSE_VALUE=20000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DEXTERNAL_CLOCK_VALUE=12288000 -DHSI_VALUE=64000000 -DLSI_VALUE=32000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=0 -DART_ACCELERATOR_ENABLE=0 -c -I../../Core/Inc -I../../Drivers/STM32H5xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"C:/Users/IRIAF-Jahad/Desktop/Table_Tester/Table_Tester_PRS20/STM32CubeIDE/Drivers/Device_Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Device_Driver

clean-Drivers-2f-Device_Driver:
	-$(RM) ./Drivers/Device_Driver/GUI.cyclo ./Drivers/Device_Driver/GUI.d ./Drivers/Device_Driver/GUI.o ./Drivers/Device_Driver/GUI.su ./Drivers/Device_Driver/RS485.cyclo ./Drivers/Device_Driver/RS485.d ./Drivers/Device_Driver/RS485.o ./Drivers/Device_Driver/RS485.su ./Drivers/Device_Driver/SPI.cyclo ./Drivers/Device_Driver/SPI.d ./Drivers/Device_Driver/SPI.o ./Drivers/Device_Driver/SPI.su ./Drivers/Device_Driver/delay.cyclo ./Drivers/Device_Driver/delay.d ./Drivers/Device_Driver/delay.o ./Drivers/Device_Driver/delay.su ./Drivers/Device_Driver/lcd.cyclo ./Drivers/Device_Driver/lcd.d ./Drivers/Device_Driver/lcd.o ./Drivers/Device_Driver/lcd.su ./Drivers/Device_Driver/xpt2046.cyclo ./Drivers/Device_Driver/xpt2046.d ./Drivers/Device_Driver/xpt2046.o ./Drivers/Device_Driver/xpt2046.su

.PHONY: clean-Drivers-2f-Device_Driver

