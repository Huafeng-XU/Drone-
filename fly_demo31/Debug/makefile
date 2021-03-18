################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv5/tools/compiler/arm_5.1.1

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./uarts.obj" \
"./tm4c123ge6pm_startup_ccs.obj" \
"./timers.obj" \
"./nrf2401.obj" \
"./mymath.obj" \
"./mpu6050.obj" \
"./main.obj" \
"./init.obj" \
"./imu_new.obj" \
"./hmc5883.obj" \
"./flow.obj" \
"./display_oled.obj" \
"./control.obj" \
"./capture.obj" \
"./US100.obj" \
"./SPI.obj" \
"./PWM.obj" \
"./IIC.obj" \
"C:/ti/TivaWare_C_Series-2.0.1.11577/driverlib/ccs/Debug/driverlib.lib" \
"../tm4c123gh6pm.cmd" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: fly_demo3.out

# Tool invocations
fly_demo3.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccsv5/tools/compiler/arm_5.1.1/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -g --diag_warning=225 --display_error_number --diag_wrap=off -z -m"fly_demo3.map" -i"C:/ti/ccsv5/tools/compiler/arm_5.1.1/lib" -i"C:/ti/ccsv5/tools/compiler/arm_5.1.1/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="fly_demo3_linkInfo.xml" --rom_model -o "fly_demo3.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(TMS470_EXECUTABLE_OUTPUTS__QUOTED) "fly_demo3.out"
	-$(RM) "IIC.pp" "PWM.pp" "SPI.pp" "US100.pp" "capture.pp" "control.pp" "display_oled.pp" "flow.pp" "hmc5883.pp" "imu_new.pp" "init.pp" "main.pp" "mpu6050.pp" "mymath.pp" "nrf2401.pp" "timers.pp" "tm4c123ge6pm_startup_ccs.pp" "uarts.pp" 
	-$(RM) "IIC.obj" "PWM.obj" "SPI.obj" "US100.obj" "capture.obj" "control.obj" "display_oled.obj" "flow.obj" "hmc5883.obj" "imu_new.obj" "init.obj" "main.obj" "mpu6050.obj" "mymath.obj" "nrf2401.obj" "timers.obj" "tm4c123ge6pm_startup_ccs.obj" "uarts.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

