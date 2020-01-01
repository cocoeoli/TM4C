################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
mydrivers/QEI_Model.obj: ../mydrivers/QEI_Model.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --include_path="F:/TM4/TivaWare_C_Series-2.1.4.178" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="mydrivers/QEI_Model.d" --obj_directory="mydrivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mydrivers/adc.obj: ../mydrivers/adc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --include_path="F:/TM4/TivaWare_C_Series-2.1.4.178" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="mydrivers/adc.d" --obj_directory="mydrivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mydrivers/key.obj: ../mydrivers/key.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --include_path="F:/TM4/TivaWare_C_Series-2.1.4.178" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="mydrivers/key.d" --obj_directory="mydrivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mydrivers/pid.obj: ../mydrivers/pid.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --include_path="F:/TM4/TivaWare_C_Series-2.1.4.178" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="mydrivers/pid.d" --obj_directory="mydrivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mydrivers/pwm.obj: ../mydrivers/pwm.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --include_path="F:/TM4/TivaWare_C_Series-2.1.4.178" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="mydrivers/pwm.d" --obj_directory="mydrivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mydrivers/uart.obj: ../mydrivers/uart.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --include_path="F:/TM4/TivaWare_C_Series-2.1.4.178" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="mydrivers/uart.d" --obj_directory="mydrivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


