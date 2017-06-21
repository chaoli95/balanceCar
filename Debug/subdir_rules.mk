################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
I2C.obj: ../I2C.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/msp430_15.12.3.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/Users/lchao/workspace_v6_2/balanceCar/driverlib/MSP430F5xx_6xx" --include_path="C:/Users/lchao/workspace_v6_2/balanceCar/MSP-EXP430F5529_HAL" --include_path="C:/ti/ccsv6/tools/compiler/msp430_15.12.3.LTS/include" -g --define=__MSP430F5529__ --diag_warning=225 --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --abi=eabi --printf_support=minimal --preproc_with_compile --preproc_dependency="I2C.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

MPU9150.obj: ../MPU9150.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/msp430_15.12.3.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/Users/lchao/workspace_v6_2/balanceCar/driverlib/MSP430F5xx_6xx" --include_path="C:/Users/lchao/workspace_v6_2/balanceCar/MSP-EXP430F5529_HAL" --include_path="C:/ti/ccsv6/tools/compiler/msp430_15.12.3.LTS/include" -g --define=__MSP430F5529__ --diag_warning=225 --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --abi=eabi --printf_support=minimal --preproc_with_compile --preproc_dependency="MPU9150.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

control.obj: ../control.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/msp430_15.12.3.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/Users/lchao/workspace_v6_2/balanceCar/driverlib/MSP430F5xx_6xx" --include_path="C:/Users/lchao/workspace_v6_2/balanceCar/MSP-EXP430F5529_HAL" --include_path="C:/ti/ccsv6/tools/compiler/msp430_15.12.3.LTS/include" -g --define=__MSP430F5529__ --diag_warning=225 --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --abi=eabi --printf_support=minimal --preproc_with_compile --preproc_dependency="control.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

filter.obj: ../filter.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/msp430_15.12.3.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/Users/lchao/workspace_v6_2/balanceCar/driverlib/MSP430F5xx_6xx" --include_path="C:/Users/lchao/workspace_v6_2/balanceCar/MSP-EXP430F5529_HAL" --include_path="C:/ti/ccsv6/tools/compiler/msp430_15.12.3.LTS/include" -g --define=__MSP430F5529__ --diag_warning=225 --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --abi=eabi --printf_support=minimal --preproc_with_compile --preproc_dependency="filter.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/msp430_15.12.3.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/Users/lchao/workspace_v6_2/balanceCar/driverlib/MSP430F5xx_6xx" --include_path="C:/Users/lchao/workspace_v6_2/balanceCar/MSP-EXP430F5529_HAL" --include_path="C:/ti/ccsv6/tools/compiler/msp430_15.12.3.LTS/include" -g --define=__MSP430F5529__ --diag_warning=225 --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --abi=eabi --printf_support=minimal --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

motor.obj: ../motor.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/msp430_15.12.3.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/Users/lchao/workspace_v6_2/balanceCar/driverlib/MSP430F5xx_6xx" --include_path="C:/Users/lchao/workspace_v6_2/balanceCar/MSP-EXP430F5529_HAL" --include_path="C:/ti/ccsv6/tools/compiler/msp430_15.12.3.LTS/include" -g --define=__MSP430F5529__ --diag_warning=225 --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --abi=eabi --printf_support=minimal --preproc_with_compile --preproc_dependency="motor.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


