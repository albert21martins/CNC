################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := c:/ti/ccsv6/tools/compiler/msp430_4.3.3

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./main.obj" \
"./ssd1289/screens.obj" \
"./ssd1289/ssd1289.obj" \
"./motors/motors_func.obj" \
"./ads7843/ads7843.obj" \
"./ads7843/position.obj" \
"./SD/sd_functions.obj" \
"./SD/pff2a/src/diskio.obj" \
"./SD/pff2a/src/pff.obj" \
"./SD/drivers/spi.obj" \
"./End_stops/end_stop.obj" \
"./End_stops/gcode.obj" \
"./End_stops/step_driver.obj" \
"./End_stops/timers.obj" \
"../lnk_msp430f5529.cmd" \
-l"libc.a" \
-l"libmath.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include ssd1289/subdir_vars.mk
-include motors/subdir_vars.mk
-include ads7843/subdir_vars.mk
-include SD/subdir_vars.mk
-include SD/pff2a/src/subdir_vars.mk
-include SD/drivers/subdir_vars.mk
-include End_stops/subdir_vars.mk
-include subdir_rules.mk
-include ssd1289/subdir_rules.mk
-include motors/subdir_rules.mk
-include ads7843/subdir_rules.mk
-include SD/subdir_rules.mk
-include SD/pff2a/src/subdir_rules.mk
-include SD/drivers/subdir_rules.mk
-include End_stops/subdir_rules.mk
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
EXE_OUTPUTS += \
CNC.out \

EXE_OUTPUTS__QUOTED += \
"CNC.out" \

BIN_OUTPUTS += \
CNC.hex \

BIN_OUTPUTS__QUOTED += \
"CNC.hex" \


# All Target
all: CNC.out

# Tool invocations
CNC.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmspx --abi=eabi --data_model=restricted --advice:power=all -g --define=__MSP430F5529__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=minimal -z -m"CNC.map" --heap_size=160 --stack_size=160 --use_hw_mpy=F5 --cinit_hold_wdt=on -i"c:/ti/ccsv6/ccs_base/msp430/include" -i"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/lib" -i"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/include" -i"c:/ti/ccsv6/ccs_base/msp430/lib/5xx_6xx_FRxx" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="CNC_linkInfo.xml" --rom_model -o "CNC.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

CNC.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: MSP430 Hex Utility'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/hex430" --memwidth=8 --romwidth=8 -o "CNC.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "main.pp" "ssd1289\screens.pp" "ssd1289\ssd1289.pp" "motors\motors_func.pp" "ads7843\ads7843.pp" "ads7843\position.pp" "SD\sd_functions.pp" "SD\pff2a\src\diskio.pp" "SD\pff2a\src\pff.pp" "SD\drivers\spi.pp" "End_stops\end_stop.pp" "End_stops\gcode.pp" "End_stops\step_driver.pp" "End_stops\timers.pp" 
	-$(RM) "main.obj" "ssd1289\screens.obj" "ssd1289\ssd1289.obj" "motors\motors_func.obj" "ads7843\ads7843.obj" "ads7843\position.obj" "SD\sd_functions.obj" "SD\pff2a\src\diskio.obj" "SD\pff2a\src\pff.obj" "SD\drivers\spi.obj" "End_stops\end_stop.obj" "End_stops\gcode.obj" "End_stops\step_driver.obj" "End_stops\timers.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

