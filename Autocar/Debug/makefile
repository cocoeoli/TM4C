################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./interrupt_handler.obj" \
"./main.obj" \
"./route_plan.obj" \
"./tm4c123gh6pm_startup_ccs.obj" \
"./uartstdio.obj" \
"./drivers/ESP8266/esp8266.obj" \
"./drivers/PID/pid.obj" \
"./drivers/car_ctrl/car_ctrl.obj" \
"./drivers/key/key.obj" \
"./drivers/mpu6050/I2C_Init.obj" \
"./drivers/mpu6050/MPU6050.obj" \
"./drivers/mpu6050/inv_mpu.obj" \
"./drivers/mpu6050/inv_mpu_dmp_motion_driver.obj" \
"./drivers/my_delay/delay.obj" \
"./drivers/pwm/pwm_config.obj" \
"./drivers/timer/timer_config.obj" \
"./drivers/timer/wtimer.obj" \
"./drivers/uart/uart.obj" \
"./drivers/ultra/distance.obj" \
"F:/TM4/TivaWare_C_Series-2.1.4.178/driverlib/ccs/Debug/driverlib.lib" \
"../tm4c123gh6pm.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \
-l"F:/TM4/TivaWare_C_Series-2.1.4.178/driverlib/ccs/Debug/driverlib.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include drivers/ESP8266/subdir_vars.mk
-include drivers/PID/subdir_vars.mk
-include drivers/car_ctrl/subdir_vars.mk
-include drivers/key/subdir_vars.mk
-include drivers/mpu6050/subdir_vars.mk
-include drivers/my_delay/subdir_vars.mk
-include drivers/pwm/subdir_vars.mk
-include drivers/timer/subdir_vars.mk
-include drivers/uart/subdir_vars.mk
-include drivers/ultra/subdir_vars.mk
-include subdir_rules.mk
-include drivers/ESP8266/subdir_rules.mk
-include drivers/PID/subdir_rules.mk
-include drivers/car_ctrl/subdir_rules.mk
-include drivers/key/subdir_rules.mk
-include drivers/mpu6050/subdir_rules.mk
-include drivers/my_delay/subdir_rules.mk
-include drivers/pwm/subdir_rules.mk
-include drivers/timer/subdir_rules.mk
-include drivers/uart/subdir_rules.mk
-include drivers/ultra/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Autocar.out \

EXE_OUTPUTS__QUOTED += \
"Autocar.out" \

BIN_OUTPUTS += \
Autocar.hex \

BIN_OUTPUTS__QUOTED += \
"Autocar.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "Autocar.out"

# Tool invocations
Autocar.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"Autocar.map" --heap_size=128 --stack_size=512 -i"F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/lib" -i"F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="Autocar_linkInfo.xml" --rom_model -o "Autocar.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

Autocar.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: ARM Hex Utility'
	"F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armhex"  -o "Autocar.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "interrupt_handler.obj" "main.obj" "route_plan.obj" "tm4c123gh6pm_startup_ccs.obj" "uartstdio.obj" "drivers\ESP8266\esp8266.obj" "drivers\PID\pid.obj" "drivers\car_ctrl\car_ctrl.obj" "drivers\key\key.obj" "drivers\mpu6050\I2C_Init.obj" "drivers\mpu6050\MPU6050.obj" "drivers\mpu6050\inv_mpu.obj" "drivers\mpu6050\inv_mpu_dmp_motion_driver.obj" "drivers\my_delay\delay.obj" "drivers\pwm\pwm_config.obj" "drivers\timer\timer_config.obj" "drivers\timer\wtimer.obj" "drivers\uart\uart.obj" "drivers\ultra\distance.obj" 
	-$(RM) "interrupt_handler.d" "main.d" "route_plan.d" "tm4c123gh6pm_startup_ccs.d" "uartstdio.d" "drivers\ESP8266\esp8266.d" "drivers\PID\pid.d" "drivers\car_ctrl\car_ctrl.d" "drivers\key\key.d" "drivers\mpu6050\I2C_Init.d" "drivers\mpu6050\MPU6050.d" "drivers\mpu6050\inv_mpu.d" "drivers\mpu6050\inv_mpu_dmp_motion_driver.d" "drivers\my_delay\delay.d" "drivers\pwm\pwm_config.d" "drivers\timer\timer_config.d" "drivers\timer\wtimer.d" "drivers\uart\uart.d" "drivers\ultra\distance.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

