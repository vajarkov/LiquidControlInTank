SHELL := cmd.exe
CYGWIN=nontsec
export PATH := C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\Users\Вадим Жарков\AppData\Local\Microsoft\WindowsApps;C:\Program Files (x86)\Common Files\Hilscher GmbH\TLRDecode;C:\Users\Вадим Жарков\AppData\Local\Microsoft\WindowsApps;C:\Program Files (x86)\Common Files\Hilscher GmbH\TLRDecode
export AS_BUILD_MODE := Rebuild
export AS_VERSION := 4.3.7.46 SP
export AS_COMPANY_NAME :=  
export AS_USER_NAME := Вадим Жарков
export AS_PATH := C:/BrAutomation/AS43
export AS_BIN_PATH := C:/BrAutomation/AS43/Bin-en
export AS_PROJECT_PATH := C:/Projects/LiquidControlInTank
export AS_PROJECT_NAME := LiquidControlOfTank
export AS_SYSTEM_PATH := C:/BrAutomation/AS/System
export AS_VC_PATH := C:/BrAutomation/AS43/AS/VC
export AS_TEMP_PATH := C:/Projects/LiquidControlInTank/Temp
export AS_CONFIGURATION := Config3
export AS_BINARIES_PATH := C:/Projects/LiquidControlInTank/Binaries
export AS_GNU_INST_PATH := C:/BrAutomation/AS43/AS/GnuInst/V4.1.2
export AS_GNU_BIN_PATH := $(AS_GNU_INST_PATH)/bin
export AS_GNU_INST_PATH_SUB_MAKE := C:/BrAutomation/AS43/AS/GnuInst/V4.1.2
export AS_GNU_BIN_PATH_SUB_MAKE := $(AS_GNU_INST_PATH_SUB_MAKE)/bin
export AS_INSTALL_PATH := C:/BrAutomation/AS43
export WIN32_AS_PATH := "C:\BrAutomation\AS43"
export WIN32_AS_BIN_PATH := "C:\BrAutomation\AS43\Bin-en"
export WIN32_AS_PROJECT_PATH := "C:\Projects\LiquidControlInTank"
export WIN32_AS_SYSTEM_PATH := "C:\BrAutomation\AS\System"
export WIN32_AS_VC_PATH := "C:\BrAutomation\AS43\AS\VC"
export WIN32_AS_TEMP_PATH := "C:\Projects\LiquidControlInTank\Temp"
export WIN32_AS_BINARIES_PATH := "C:\Projects\LiquidControlInTank\Binaries"
export WIN32_AS_GNU_INST_PATH := "C:\BrAutomation\AS43\AS\GnuInst\V4.1.2"
export WIN32_AS_GNU_BIN_PATH := "$(WIN32_AS_GNU_INST_PATH)\\bin" 
export WIN32_AS_INSTALL_PATH := "C:\BrAutomation\AS43"

.suffixes:

ProjectMakeFile:

	@'$(AS_BIN_PATH)/BR.AS.AnalyseProject.exe' '$(AS_PROJECT_PATH)/LiquidControlOfTank.apj' -t '$(AS_TEMP_PATH)' -c '$(AS_CONFIGURATION)' -o '$(AS_BINARIES_PATH)'   -sfas -buildMode 'Rebuild'   

	@$(AS_GNU_BIN_PATH)/mingw32-make.exe -r -f 'C:/Projects/LiquidControlInTank/Temp/Objects/$(AS_CONFIGURATION)/X20CP1301/#cpu.mak' -k 

