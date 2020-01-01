################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./tm4c123gh6pm_startup_ccs.obj" \
"./uartstdio.obj" \
"./mydrivers/QEI/QEI_Model.obj" \
"./mydrivers/adc/adc.obj" \
"./mydrivers/key/key.obj" \
"./mydrivers/mpu6050/I2C_Init.obj" \
"./mydrivers/mpu6050/MPU6050.obj" \
"./mydrivers/mpu6050/inv_mpu.obj" \
"./mydrivers/mpu6050/inv_mpu_dmp_motion_driver.obj" \
"./mydrivers/my_delay/delay.obj" \
"./mydrivers/pid/pid.obj" \
"./mydrivers/pwm/pwm.obj" \
"./mydrivers/timer/timer.obj" \
"./mydrivers/uart/uart.obj" \
"F:/TM4/TivaWare_C_Series-2.1.4.178/driverlib/ccs/Debug/driverlib.lib" \
"../tm4c123gh6pm.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include mydrivers/QEI/subdir_vars.mk
-include mydrivers/adc/subdir_vars.mk
-include mydrivers/key/subdir_vars.mk
-include mydrivers/mpu6050/subdir_vars.mk
-include mydrivers/my_delay/subdir_vars.mk
-include mydrivers/pid/subdir_vars.mk
-include mydrivers/pwm/subdir_vars.mk
-include mydrivers/timer/subdir_vars.mk
-include mydrivers/uart/subdir_vars.mk
-include subdir_rules.mk
-include mydrivers/QEI/subdir_rules.mk
-include mydrivers/adc/subdir_rules.mk
-include mydrivers/key/subdir_rules.mk
-include mydrivers/mpu6050/subdir_rules.mk
-include mydrivers/my_delay/subdir_rules.mk
-include mydrivers/pid/subdir_rules.mk
-include mydrivers/pwm/subdir_rules.mk
-include mydrivers/timer/subdir_rules.mk
-include mydrivers/uart/subdir_rules.mk
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
InvertedPendulum.out \

EXE_OUTPUTS__QUOTED += \
"InvertedPendulum.out" \

BIN_OUTPUTS += \
InvertedPendulum.hex \

BIN_OUTPUTS__QUOTED += \
"InvertedPendulum.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "InvertedPendulum.out"

# Tool invocations
InvertedPendulum.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"InvertedPendulum.map" --heap_size=0 --stack_size=512 -i"F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/lib" -i"F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="InvertedPendulum_linkInfo.xml" --rom_model -o "InvertedPendulum.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

InvertedPendulum.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: ARM Hex Utility'
	"F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armhex"  -o "InvertedPendulum.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "tm4c123gh6pm_startup_ccs.obj" "uartstdio.obj" "mydrivers\QEI\QEI_Model.obj" "mydrivers\adc\adc.obj" "mydrivers\key\key.obj" "mydrivers\mpu6050\I2C_Init.obj" "mydrivers\mpu6050\MPU6050.obj" "mydrivers\mpu6050\inv_mpu.obj" "mydrivers\mpu6050\inv_mpu_dmp_motion_driver.obj" "mydrivers\my_delay\delay.obj" "mydrivers\pid\pid.obj" "mydrivers\pwm\pwm.obj" "mydrivers\timer\timer.obj" "mydrivers\uart\uart.obj" 
	-$(RM) "main.d" "tm4c123gh6pm_startup_ccs.d" "uartstdio.d" "mydrivers\QEI\QEI_Model.d" "mydrivers\adc\adc.d" "mydrivers\key\key.d" "mydrivers\mpu6050\I2C_Init.d" "mydrivers\mpu6050\MPU6050.d" "mydrivers\mpu6050\inv_mpu.d" "mydrivers\mpu6050\inv_mpu_dmp_motion_driver.d" "mydrivers\my_delay\delay.d" "mydrivers\pid\pid.d" "mydrivers\pwm\pwm.d" "mydrivers\timer\timer.d" "mydrivers\uart\uart.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

