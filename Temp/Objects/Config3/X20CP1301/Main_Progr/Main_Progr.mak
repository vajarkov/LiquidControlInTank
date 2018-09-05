UnmarkedObjectFolder := C:/Projects/LiquidControlInTank/Logical/Main_Program
MarkedObjectFolder := C:/Projects/LiquidControlInTank/Logical/Main_Program

$(AS_CPU_PATH)/Main_Progr.br: \
	$(AS_PROJECT_CPU_PATH)/Cpu.per \
	FORCE \
	$(AS_CPU_PATH)/Main_Progr/Main_Progr.ox
	@'$(AS_BIN_PATH)/BR.AS.TaskBuilder.exe' '$(AS_CPU_PATH)/Main_Progr/Main_Progr.ox' -o '$(AS_CPU_PATH)/Main_Progr.br' -v V1.00.0 -f '$(AS_CPU_PATH)/NT.ofs' -offsetLT '$(AS_BINARIES_PATH)/$(AS_CONFIGURATION)/$(AS_PLC)/LT.ofs' -T SG4  -M IA32  -B E4.34 -extConstants -r Cyclic4 -p 3 -s 'Main_Program' -L 'AsBrStr: V*, AsIecCon: V*, asstring: V*, astime: V*, become: V1.00.0, DataObj: V*, DRV_mbus: V*, dvframe: V*, operator: V*, runtime: V*, standard: V*' -P '$(AS_PROJECT_PATH)' -secret '$(AS_PROJECT_PATH)_br.as.taskbuilder.exe'

$(AS_CPU_PATH)/Main_Progr/Main_Progr.ox: \
	$(AS_CPU_PATH)/Main_Progr/a.out \
	FORCE 
	@'$(AS_BIN_PATH)/BR.AS.Backend.exe' '$(AS_CPU_PATH)/Main_Progr/a.out' -o '$(AS_CPU_PATH)/Main_Progr/Main_Progr.ox' -T SG4 -r Cyclic4   -G V4.1.2  -B E4.34 -secret '$(AS_PROJECT_PATH)_br.as.backend.exe'

$(AS_CPU_PATH)/Main_Progr/a.out: \
	$(AS_CPU_PATH)/Main_Progr/Cyclic.c.o \
	$(AS_CPU_PATH)/Main_Progr/Init.c.o \
	$(AS_CPU_PATH)/Main_Progr/Exit.c.o \
	$(AS_CPU_PATH)/Main_Progr/_bur_pvdef.c.o \
	FORCE
	@'$(AS_BIN_PATH)/BR.AS.CCompiler.exe' -link '$(AS_CPU_PATH)/Main_Progr/Cyclic.c.o' '$(AS_CPU_PATH)/Main_Progr/Init.c.o' '$(AS_CPU_PATH)/Main_Progr/Exit.c.o' '$(AS_CPU_PATH)/Main_Progr/_bur_pvdef.c.o'  -o '$(AS_CPU_PATH)/Main_Progr/a.out'  -G V4.1.2  -T SG4  -M IA32  '-Wl,$(AS_SYSTEM_PATH)/E0434/SG4/IA32/libDRV_mbus.a' '-Wl,$(AS_SYSTEM_PATH)/E0434/SG4/IA32/libdvframe.a' '-Wl,$(AS_TEMP_PATH)/Archives/$(AS_CONFIGURATION)/$(AS_PLC)/libbecome.a' '-Wl,$(AS_SYSTEM_PATH)/E0434/SG4/IA32/libstandard.a' '-Wl,$(AS_SYSTEM_PATH)/E0434/SG4/IA32/libDataObj.a' '-Wl,$(AS_SYSTEM_PATH)/E0434/SG4/IA32/libAsBrStr.a' '-Wl,$(AS_SYSTEM_PATH)/E0434/SG4/IA32/libasstring.a' '-Wl,$(AS_SYSTEM_PATH)/E0434/SG4/IA32/libAsIecCon.a' '-Wl,$(AS_SYSTEM_PATH)/E0434/SG4/IA32/libastime.a' '-Wl,$(AS_SYSTEM_PATH)/E0434/SG4/IA32/libruntime.a' '-Wl,$(AS_SYSTEM_PATH)/E0434/SG4/IA32/liboperator.a' -specs=I386specs_brelf -secret '$(AS_PROJECT_PATH)_br.as.ccompiler.exe'

$(AS_CPU_PATH)/Main_Progr/Cyclic.c.o: \
	$(AS_PROJECT_PATH)/Logical/Main_Program/Cyclic.c \
	FORCE 
	@'$(AS_BIN_PATH)/BR.AS.CCompiler.exe' '$(AS_PROJECT_PATH)/Logical/Main_Program/Cyclic.c' -o '$(AS_CPU_PATH)/Main_Progr/Cyclic.c.o'  -T SG4  -M IA32  -B E4.34 -G V4.1.2  -s 'Main_Program' -t '$(AS_TEMP_PATH)' -specs=I386specs_brelf -I '$(AS_PROJECT_PATH)/Logical/Main_Program' '$(AS_TEMP_PATH)/Includes/Main_Program' '$(AS_TEMP_PATH)/Includes' -trigraphs -fno-asm -D _DEFAULT_INCLUDES -D _SG4 -fPIC -O0 -g -Wall -include '$(AS_CPU_PATH)/Libraries.h' -x c -P '$(AS_PROJECT_PATH)' -secret '$(AS_PROJECT_PATH)_br.as.ccompiler.exe'

$(AS_CPU_PATH)/Main_Progr/Init.c.o: \
	$(AS_PROJECT_PATH)/Logical/Main_Program/Init.c \
	FORCE 
	@'$(AS_BIN_PATH)/BR.AS.CCompiler.exe' '$(AS_PROJECT_PATH)/Logical/Main_Program/Init.c' -o '$(AS_CPU_PATH)/Main_Progr/Init.c.o'  -T SG4  -M IA32  -B E4.34 -G V4.1.2  -s 'Main_Program' -t '$(AS_TEMP_PATH)' -specs=I386specs_brelf -I '$(AS_PROJECT_PATH)/Logical/Main_Program' '$(AS_TEMP_PATH)/Includes/Main_Program' '$(AS_TEMP_PATH)/Includes' -trigraphs -fno-asm -D _DEFAULT_INCLUDES -D _SG4 -fPIC -O0 -g -Wall -include '$(AS_CPU_PATH)/Libraries.h' -x c -P '$(AS_PROJECT_PATH)' -secret '$(AS_PROJECT_PATH)_br.as.ccompiler.exe'

$(AS_CPU_PATH)/Main_Progr/Exit.c.o: \
	$(AS_PROJECT_PATH)/Logical/Main_Program/Exit.c \
	FORCE 
	@'$(AS_BIN_PATH)/BR.AS.CCompiler.exe' '$(AS_PROJECT_PATH)/Logical/Main_Program/Exit.c' -o '$(AS_CPU_PATH)/Main_Progr/Exit.c.o'  -T SG4  -M IA32  -B E4.34 -G V4.1.2  -s 'Main_Program' -t '$(AS_TEMP_PATH)' -specs=I386specs_brelf -I '$(AS_PROJECT_PATH)/Logical/Main_Program' '$(AS_TEMP_PATH)/Includes/Main_Program' '$(AS_TEMP_PATH)/Includes' -trigraphs -fno-asm -D _DEFAULT_INCLUDES -D _SG4 -fPIC -O0 -g -Wall -include '$(AS_CPU_PATH)/Libraries.h' -x c -P '$(AS_PROJECT_PATH)' -secret '$(AS_PROJECT_PATH)_br.as.ccompiler.exe'

$(AS_CPU_PATH)/Main_Progr/_bur_pvdef.c.o: \
	FORCE 
	@'$(AS_BIN_PATH)/BR.AS.CCompiler.exe' '$(AS_PATH)/AS/GnuInst/V4.1.2/i386-elf/include/bur/_bur_pvdef.c' -o '$(AS_CPU_PATH)/Main_Progr/_bur_pvdef.c.o'  -T SG4  -M IA32  -B E4.34 -G V4.1.2  -s 'Main_Program' -t '$(AS_TEMP_PATH)' -specs=I386specs_brelf -I '$(AS_PROJECT_PATH)/Logical/Main_Program' '$(AS_TEMP_PATH)/Includes/Main_Program' '$(AS_TEMP_PATH)/Includes' -trigraphs -fno-asm -D _DEFAULT_INCLUDES -D _SG4 -fPIC -O0 -g -Wall -include '$(AS_CPU_PATH)/Libraries.h' -P '$(AS_PROJECT_PATH)' 
 -secret '$(AS_PROJECT_PATH)_br.as.ccompiler.exe'

-include $(AS_CPU_PATH)/Force.mak 



FORCE: