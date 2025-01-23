################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/Table_Tester/Common_CONST_VAR.c \
../Application/User/Table_Tester/Table_Tester_App.c 

OBJS += \
./Application/User/Table_Tester/Common_CONST_VAR.o \
./Application/User/Table_Tester/Table_Tester_App.o 

C_DEPS += \
./Application/User/Table_Tester/Common_CONST_VAR.d \
./Application/User/Table_Tester/Table_Tester_App.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Table_Tester/%.o Application/User/Table_Tester/%.su Application/User/Table_Tester/%.cyclo: ../Application/User/Table_Tester/%.c Application/User/Table_Tester/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DSTM32H573xx -DHSE_VALUE=20000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DEXTERNAL_CLOCK_VALUE=12288000 -DHSI_VALUE=64000000 -DLSI_VALUE=32000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=0 -DART_ACCELERATOR_ENABLE=0 -c -I../../Core/Inc -I../../Drivers/STM32H5xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"C:/Users/IRIAF-Jahad/Desktop/Table_Tester/Table_Tester_PRS20/STM32CubeIDE/Drivers/Device_Driver" -I"C:/Users/IRIAF-Jahad/Desktop/Table_Tester/Table_Tester_PRS20/STM32CubeIDE/Application/User/Table_Tester" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User-2f-Table_Tester

clean-Application-2f-User-2f-Table_Tester:
	-$(RM) ./Application/User/Table_Tester/Common_CONST_VAR.cyclo ./Application/User/Table_Tester/Common_CONST_VAR.d ./Application/User/Table_Tester/Common_CONST_VAR.o ./Application/User/Table_Tester/Common_CONST_VAR.su ./Application/User/Table_Tester/Table_Tester_App.cyclo ./Application/User/Table_Tester/Table_Tester_App.d ./Application/User/Table_Tester/Table_Tester_App.o ./Application/User/Table_Tester/Table_Tester_App.su

.PHONY: clean-Application-2f-User-2f-Table_Tester

