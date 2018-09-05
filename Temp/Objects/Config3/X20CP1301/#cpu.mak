SHELL = cmd.exe
export AS_PLC := X20CP1301
export AS_TEMP_PLC := X20CP1301
export AS_CPU_PATH := $(AS_TEMP_PATH)/Objects/$(AS_CONFIGURATION)/$(AS_PLC)
export AS_CPU_PATH_2 := C:/Projects/LiquidControlInTank/Temp//Objects/$(AS_CONFIGURATION)/$(AS_PLC)
export AS_PROJECT_CONFIG_PATH := $(AS_PROJECT_PATH)/Physical/$(AS_CONFIGURATION)
export AS_PROJECT_CPU_PATH := $(AS_PROJECT_CONFIG_PATH)/$(AS_PLC)
export AS_STATIC_ARCHIVES_PATH := $(AS_TEMP_PATH)/Archives/$(AS_CONFIGURATION)/$(AS_PLC)
export WIN32_AS_CPU_PATH := $(WIN32_AS_TEMP_PATH)\Objects\$(AS_CONFIGURATION)\$(AS_PLC)
export WIN32_AS_ACTIVE_CONFIG_PATH := $(WIN32_AS_PROJECT_PATH)\Physical\$(AS_CONFIGURATION)\$(AS_PLC)
export AS_FILES_TO_TRANSFER := $(AS_TEMP_PATH)/Transfer/$(AS_CONFIGURATION)/$(AS_PLC)/FilesToTransfer


CpuMakeFile: \
$(AS_CPU_PATH)/ashwd.br \
$(AS_CPU_PATH)/asfw.br \
$(AS_CPU_PATH)/sysconf.br \
$(AS_CPU_PATH)/arconfig.br \
$(AS_CPU_PATH)/ashwac.br \
$(AS_CPU_PATH)/become.br \
$(AS_CPU_PATH)/Visu_1.br \
$(AS_CPU_PATH)/Main_Progr.br \
$(AS_CPU_PATH)/Slave.br \
$(AS_CPU_PATH)/datamod.br \
$(AS_CPU_PATH)/Visu1.br \
$(AS_CPU_PATH)/iomap.br \
$(AS_CPU_PATH)/Role.br \
$(AS_CPU_PATH)/User.br \
$(AS_CPU_PATH)/TCData.br \
$(AS_BINARIES_PATH)/$(AS_CONFIGURATION)/$(AS_PLC)/Transfer.lst


$(AS_BINARIES_PATH)/$(AS_CONFIGURATION)/$(AS_PLC)/Transfer.lst: \
	FORCE
	@'$(AS_BIN_PATH)/BR.AS.FinalizeBuild.exe' '$(AS_PROJECT_PATH)/LiquidControlOfTank.apj' -t '$(AS_TEMP_PATH)' -o '$(AS_BINARIES_PATH)' -c '$(AS_CONFIGURATION)' -i 'C:/BrAutomation/AS43' -S 'X20CP1301'  -all -A 'X20CP1301' -pil   -swFiles '$(AS_PROJECT_PATH)/Physical/Config3/X20CP1301/Cpu.sw' -Z 'Acp10Arnc0: 3.18.2, mapp: 1.62.1, UnitSystem: n.d, TextSystem: n.d, Connectivity: n.d, AAS: n.d' -C '/RT=1000 /AM=* /SDT=5 /DAIP=192.168.1.100 /REPO=11159 /ANSL=1 /PT=11169' -D '/IF=tcpip /LOPO=11159 /SA=1' -M IA32 -T SG4

#nothing to do (just call module make files)

include $(AS_CPU_PATH)/TCData/TCData.mak
include $(AS_CPU_PATH)/User/User.mak
include $(AS_CPU_PATH)/Role/Role.mak
include $(AS_CPU_PATH)/iomap/iomap.mak
include $(AS_CPU_PATH)/Visu1/Visu1.mak
include $(AS_CPU_PATH)/datamod/datamod.mak
include $(AS_CPU_PATH)/Slave/Slave.mak
include $(AS_CPU_PATH)/Main_Progr/Main_Progr.mak
include $(AS_CPU_PATH)/Visu_1/Visu_1.mak
include $(AS_CPU_PATH)/become/become.mak
include $(AS_CPU_PATH)/ashwac/ashwac.mak
include $(AS_CPU_PATH)/arconfig/arconfig.mak
include $(AS_CPU_PATH)/sysconf/sysconf.mak
include $(AS_CPU_PATH)/asfw/asfw.mak
include $(AS_CPU_PATH)/ashwd/ashwd.mak

.DEFAULT:
#nothing to do (need this target for prerequisite files that don't exit)

FORCE:
