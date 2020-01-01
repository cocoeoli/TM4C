################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
mydrivers/mpu6050/I2C_Init.obj: ../mydrivers/mpu6050/I2C_Init.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --include_path="F:/TM4/TivaWare_C_Series-2.1.4.178" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="mydrivers/mpu6050/I2C_Init.d" --obj_directory="mydrivers/mpu6050" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mydrivers/mpu6050/MPU6050.obj: ../mydrivers/mpu6050/MPU6050.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --include_path="F:/TM4/TivaWare_C_Series-2.1.4.178" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="mydrivers/mpu6050/MPU6050.d" --obj_directory="mydrivers/mpu6050" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mydrivers/mpu6050/inv_mpu.obj: ../mydrivers/mpu6050/inv_mpu.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --include_path="F:/TM4/TivaWare_C_Series-2.1.4.178" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="mydrivers/mpu6050/inv_mpu.d" --obj_directory="mydrivers/mpu6050" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mydrivers/mpu6050/inv_mpu_dmp_motion_driver.obj: ../mydrivers/mpu6050/inv_mpu_dmp_motion_driver.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --include_path="F:/TM4/TivaWare_C_Series-2.1.4.178" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="mydrivers/mpu6050/inv_mpu_dmp_motion_driver.d" --obj_directory="mydrivers/mpu6050" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


