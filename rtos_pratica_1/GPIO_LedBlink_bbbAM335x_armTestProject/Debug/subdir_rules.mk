################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
GPIO_bbbAM335x_board.o: /home/felipe/ti/pdk_am335x_1_0_9/packages/ti/drv/gpio/test/led_blink/src/am335x/GPIO_bbbAM335x_board.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"/home/felipe/ti/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc" -c -mcpu=cortex-a8 -mtune=cortex-a8 -march=armv7-a -marm -mfloat-abi=hard -Dam3359 -DSOC_AM335x -DbbbAM335x -I"/home/felipe/Arquivos_RTOS/GPIO_LedBlink_bbbAM335x_armTestProject" -I"/home/felipe/ti/gcc-arm-none-eabi-6-2017-q1-update/arm-none-eabi/include/newlib-nano" -I"/home/felipe/ti/pdk_am335x_1_0_9/packages/ti/drv/gpio" -I"/home/felipe/ti/pdk_am335x_1_0_9/packages" -I"/packages" -I"/home/felipe/ti/gcc-arm-none-eabi-6-2017-q1-update/arm-none-eabi/include" -g -gdwarf-3 -gstrict-dwarf -Wall -finstrument-functions -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

GPIO_log.o: /home/felipe/ti/pdk_am335x_1_0_9/packages/ti/drv/gpio/test/led_blink/src/GPIO_log.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"/home/felipe/ti/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc" -c -mcpu=cortex-a8 -mtune=cortex-a8 -march=armv7-a -marm -mfloat-abi=hard -Dam3359 -DSOC_AM335x -DbbbAM335x -I"/home/felipe/Arquivos_RTOS/GPIO_LedBlink_bbbAM335x_armTestProject" -I"/home/felipe/ti/gcc-arm-none-eabi-6-2017-q1-update/arm-none-eabi/include/newlib-nano" -I"/home/felipe/ti/pdk_am335x_1_0_9/packages/ti/drv/gpio" -I"/home/felipe/ti/pdk_am335x_1_0_9/packages" -I"/packages" -I"/home/felipe/ti/gcc-arm-none-eabi-6-2017-q1-update/arm-none-eabi/include" -g -gdwarf-3 -gstrict-dwarf -Wall -finstrument-functions -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

GPIO_soc.o: /home/felipe/ti/pdk_am335x_1_0_9/packages/ti/drv/gpio/soc/am335x/GPIO_soc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"/home/felipe/ti/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc" -c -mcpu=cortex-a8 -mtune=cortex-a8 -march=armv7-a -marm -mfloat-abi=hard -Dam3359 -DSOC_AM335x -DbbbAM335x -I"/home/felipe/Arquivos_RTOS/GPIO_LedBlink_bbbAM335x_armTestProject" -I"/home/felipe/ti/gcc-arm-none-eabi-6-2017-q1-update/arm-none-eabi/include/newlib-nano" -I"/home/felipe/ti/pdk_am335x_1_0_9/packages/ti/drv/gpio" -I"/home/felipe/ti/pdk_am335x_1_0_9/packages" -I"/packages" -I"/home/felipe/ti/gcc-arm-none-eabi-6-2017-q1-update/arm-none-eabi/include" -g -gdwarf-3 -gstrict-dwarf -Wall -finstrument-functions -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

I2C_soc.o: /home/felipe/ti/pdk_am335x_1_0_9/packages/ti/drv/i2c/soc/am335x/I2C_soc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"/home/felipe/ti/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc" -c -mcpu=cortex-a8 -mtune=cortex-a8 -march=armv7-a -marm -mfloat-abi=hard -Dam3359 -DSOC_AM335x -DbbbAM335x -I"/home/felipe/Arquivos_RTOS/GPIO_LedBlink_bbbAM335x_armTestProject" -I"/home/felipe/ti/gcc-arm-none-eabi-6-2017-q1-update/arm-none-eabi/include/newlib-nano" -I"/home/felipe/ti/pdk_am335x_1_0_9/packages/ti/drv/gpio" -I"/home/felipe/ti/pdk_am335x_1_0_9/packages" -I"/packages" -I"/home/felipe/ti/gcc-arm-none-eabi-6-2017-q1-update/arm-none-eabi/include" -g -gdwarf-3 -gstrict-dwarf -Wall -finstrument-functions -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

UART_soc.o: /home/felipe/ti/pdk_am335x_1_0_9/packages/ti/drv/uart/soc/am335x/UART_soc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"/home/felipe/ti/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc" -c -mcpu=cortex-a8 -mtune=cortex-a8 -march=armv7-a -marm -mfloat-abi=hard -Dam3359 -DSOC_AM335x -DbbbAM335x -I"/home/felipe/Arquivos_RTOS/GPIO_LedBlink_bbbAM335x_armTestProject" -I"/home/felipe/ti/gcc-arm-none-eabi-6-2017-q1-update/arm-none-eabi/include/newlib-nano" -I"/home/felipe/ti/pdk_am335x_1_0_9/packages/ti/drv/gpio" -I"/home/felipe/ti/pdk_am335x_1_0_9/packages" -I"/packages" -I"/home/felipe/ti/gcc-arm-none-eabi-6-2017-q1-update/arm-none-eabi/include" -g -gdwarf-3 -gstrict-dwarf -Wall -finstrument-functions -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

build-861389649:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-861389649-inproc

build-861389649-inproc: /home/felipe/ti/pdk_am335x_1_0_9/packages/ti/drv/gpio/test/led_blink/am335x/armv7/bios/am335x_app_bbbam335x.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"/home/felipe/ti/xdctools_3_50_03_33_core/xs" --xdcpath="/home/felipe/ti/bios_6_52_00_12/packages;/home/felipe/ti/pdk_am335x_1_0_9/packages;/home/felipe/ti/edma3_lld_2_12_05_30B/packages;/home/felipe/ti/ndk_2_26_00_08/packages;/home/felipe/ti/ccsv7/ccs_base;" xdc.tools.configuro -o configPkg -t gnu.targets.arm.A8F -p ti.platforms.evmAM3359 -r debug -c "/home/felipe/ti/gcc-arm-none-eabi-6-2017-q1-update" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-861389649 /home/felipe/ti/pdk_am335x_1_0_9/packages/ti/drv/gpio/test/led_blink/am335x/armv7/bios/am335x_app_bbbam335x.cfg
configPkg/compiler.opt: build-861389649
configPkg/: build-861389649

main_led_blink.o: /home/felipe/ti/pdk_am335x_1_0_9/packages/ti/drv/gpio/test/led_blink/src/main_led_blink.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"/home/felipe/ti/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc" -c -mcpu=cortex-a8 -mtune=cortex-a8 -march=armv7-a -marm -mfloat-abi=hard -Dam3359 -DSOC_AM335x -DbbbAM335x -I"/home/felipe/Arquivos_RTOS/GPIO_LedBlink_bbbAM335x_armTestProject" -I"/home/felipe/ti/gcc-arm-none-eabi-6-2017-q1-update/arm-none-eabi/include/newlib-nano" -I"/home/felipe/ti/pdk_am335x_1_0_9/packages/ti/drv/gpio" -I"/home/felipe/ti/pdk_am335x_1_0_9/packages" -I"/packages" -I"/home/felipe/ti/gcc-arm-none-eabi-6-2017-q1-update/arm-none-eabi/include" -g -gdwarf-3 -gstrict-dwarf -Wall -finstrument-functions -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


