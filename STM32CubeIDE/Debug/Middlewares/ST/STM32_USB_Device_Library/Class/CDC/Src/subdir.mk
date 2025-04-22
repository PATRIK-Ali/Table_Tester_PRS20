################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/IRIAF-Jahad/Desktop/Table_Tester/Table_Tester_PRS20/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c \
C:/Users/IRIAF-Jahad/Desktop/Table_Tester/Table_Tester_PRS20/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc_if.c 

OBJS += \
./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.o \
./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc_if.o 

C_DEPS += \
./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.d \
./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc_if.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.o: C:/Users/IRIAF-Jahad/Desktop/Table_Tester/Table_Tester_PRS20/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DUSE_FULL_HAL_DRIVER -DSTM32H573xx -DHSE_VALUE=20000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DEXTERNAL_CLOCK_VALUE=12288000 -DHSI_VALUE=64000000 -DLSI_VALUE=32000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=0 -DART_ACCELERATOR_ENABLE=0 -c -I../../Core/Inc -I"C:/Users/IRIAF-Jahad/Desktop/Table_Tester/Table_Tester_PRS20/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/IRIAF-Jahad/Desktop/Table_Tester/Table_Tester_PRS20/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I../../Drivers/STM32H5xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"C:/Users/IRIAF-Jahad/Desktop/Table_Tester/Table_Tester_PRS20/STM32CubeIDE/Drivers/Device_Driver" -I"C:/Users/IRIAF-Jahad/Desktop/Table_Tester/Table_Tester_PRS20/STM32CubeIDE/Application/User/Table_Tester" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc_if.o: C:/Users/IRIAF-Jahad/Desktop/Table_Tester/Table_Tester_PRS20/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc_if.c Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DUSE_FULL_HAL_DRIVER -DSTM32H573xx -DHSE_VALUE=20000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DEXTERNAL_CLOCK_VALUE=12288000 -DHSI_VALUE=64000000 -DLSI_VALUE=32000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=0 -DART_ACCELERATOR_ENABLE=0 -c -I../../Core/Inc -I"C:/Users/IRIAF-Jahad/Desktop/Table_Tester/Table_Tester_PRS20/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/IRIAF-Jahad/Desktop/Table_Tester/Table_Tester_PRS20/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I../../Drivers/STM32H5xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"C:/Users/IRIAF-Jahad/Desktop/Table_Tester/Table_Tester_PRS20/STM32CubeIDE/Drivers/Device_Driver" -I"C:/Users/IRIAF-Jahad/Desktop/Table_Tester/Table_Tester_PRS20/STM32CubeIDE/Application/User/Table_Tester" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-STM32_USB_Device_Library-2f-Class-2f-CDC-2f-Src

clean-Middlewares-2f-ST-2f-STM32_USB_Device_Library-2f-Class-2f-CDC-2f-Src:
	-$(RM) ./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.cyclo ./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.d ./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.o ./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.su ./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc_if.cyclo ./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc_if.d ./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc_if.o ./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc_if.su

.PHONY: clean-Middlewares-2f-ST-2f-STM32_USB_Device_Library-2f-Class-2f-CDC-2f-Src

