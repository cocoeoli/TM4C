################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
My_UART.obj: ../My_UART.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="F:/TM4/workspace/Car_Control/GPIO" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="F:/TM4/workspace/Car_Control/USART_Show" --include_path="F:/TM4/workspace/Car_Control/Timer_Init" --include_path="F:/TM4/workspace/Car_Control/UART_Init" --include_path="F:/TM4/workspace/Car_Control/I2C_Init" --include_path="F:/TM4/workspace/Car_Control/mpu9150" --include_path="F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --include_path="F:/TM4/workspace/Car_Control/delay_fct" --include_path="F:/TM4/workspace/Car_Control/Motor_Set" --include_path="F:/TM4/workspace/Car_Control/oled" --include_path="F:/TM4/workspace/Car_Control/PID" --include_path="F:/TM4/workspace/Car_Control/QEI" --define=ccs="ccs" --define=TARGET_IS_TM4C123_RB1 --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="My_UART.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="F:/TM4/workspace/Car_Control/GPIO" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="F:/TM4/workspace/Car_Control/USART_Show" --include_path="F:/TM4/workspace/Car_Control/Timer_Init" --include_path="F:/TM4/workspace/Car_Control/UART_Init" --include_path="F:/TM4/workspace/Car_Control/I2C_Init" --include_path="F:/TM4/workspace/Car_Control/mpu9150" --include_path="F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --include_path="F:/TM4/workspace/Car_Control/delay_fct" --include_path="F:/TM4/workspace/Car_Control/Motor_Set" --include_path="F:/TM4/workspace/Car_Control/oled" --include_path="F:/TM4/workspace/Car_Control/PID" --include_path="F:/TM4/workspace/Car_Control/QEI" --define=ccs="ccs" --define=TARGET_IS_TM4C123_RB1 --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

tm4c123gh6pm_startup_ccs.obj: ../tm4c123gh6pm_startup_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="F:/TM4/workspace/Car_Control/GPIO" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="F:/TM4/workspace/Car_Control/USART_Show" --include_path="F:/TM4/workspace/Car_Control/Timer_Init" --include_path="F:/TM4/workspace/Car_Control/UART_Init" --include_path="F:/TM4/workspace/Car_Control/I2C_Init" --include_path="F:/TM4/workspace/Car_Control/mpu9150" --include_path="F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --include_path="F:/TM4/workspace/Car_Control/delay_fct" --include_path="F:/TM4/workspace/Car_Control/Motor_Set" --include_path="F:/TM4/workspace/Car_Control/oled" --include_path="F:/TM4/workspace/Car_Control/PID" --include_path="F:/TM4/workspace/Car_Control/QEI" --define=ccs="ccs" --define=TARGET_IS_TM4C123_RB1 --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="tm4c123gh6pm_startup_ccs.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uartstdio.obj: ../uartstdio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="F:/TM4/workspace/Car_Control/GPIO" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="F:/TM4/workspace/Car_Control/USART_Show" --include_path="F:/TM4/workspace/Car_Control/Timer_Init" --include_path="F:/TM4/workspace/Car_Control/UART_Init" --include_path="F:/TM4/workspace/Car_Control/I2C_Init" --include_path="F:/TM4/workspace/Car_Control/mpu9150" --include_path="F:/TM4/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --include_path="F:/TM4/workspace/Car_Control/delay_fct" --include_path="F:/TM4/workspace/Car_Control/Motor_Set" --include_path="F:/TM4/workspace/Car_Control/oled" --include_path="F:/TM4/workspace/Car_Control/PID" --include_path="F:/TM4/workspace/Car_Control/QEI" --define=ccs="ccs" --define=TARGET_IS_TM4C123_RB1 --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="uartstdio.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


