UnmarkedObjectFolder := C:/Projects/LiquidControlInTank/Logical/Program1
MarkedObjectFolder := C:/Projects/LiquidControlInTank/Logical/Program1

$(AS_CPU_PATH)/Program1.br: \
	$(AS_PROJECT_CPU_PATH)/Cpu.per \
	$(AS_CPU_PATH)/Program1/Program1.ox
	@'$(AS_BIN_PATH)/BR.AS.TaskBuilder.exe' '$(AS_CPU_PATH)/Program1/Program1.ox' -o '$(AS_CPU_PATH)/Program1.br' -v V1.00.0 -f '$(AS_CPU_PATH)/NT.ofs' -offsetLT '$(AS_BINARIES_PATH)/$(AS_CONFIGURATION)/$(AS_PLC)/LT.ofs' -T SG4  -M IA32  -B E4.34 -extConstants -r Cyclic4 -p 2 -s 'Program1' -L 'AsBrStr: V*, AsIecCon: V*, asstring: V*, astime: V*, become: V1.00.0, DataObj: V*, DRV_mbus: V*, dvframe: V*, operator: V*, runtime: V*, standard: V*' -P '$(AS_PROJECT_PATH)' -secret '$(AS_PROJECT_PATH)_br.as.taskbuilder.exe'

$(AS_CPU_PATH)/Program1/Program1.ox: \
	$(AS_CPU_PATH)/Program1/a.out
	@'$(AS_BIN_PATH)/BR.AS.Backend.exe' '$(AS_CPU_PATH)/Program1/a.out' -o '$(AS_CPU_PATH)/Program1/Program1.ox' -T SG4 -r Cyclic4   -G V4.1.2  -B E4.34 -secret '$(AS_PROJECT_PATH)_br.as.backend.exe'

$(AS_CPU_PATH)/Program1/a.out: \
	$(AS_CPU_PATH)/Program1/Cyclic.c.o \
	$(AS_CPU_PATH)/Program1/Init.c.o \
	$(AS_CPU_PATH)/Program1/Exit.c.o \
	$(AS_CPU_PATH)/Program1/_bur_pvdef.c.o
	@'$(AS_BIN_PATH)/BR.AS.CCompiler.exe' -link '$(AS_CPU_PATH)/Program1/Cyclic.c.o' '$(AS_CPU_PATH)/Program1/Init.c.o' '$(AS_CPU_PATH)/Program1/Exit.c.o' '$(AS_CPU_PATH)/Program1/_bur_pvdef.c.o'  -o '$(AS_CPU_PATH)/Program1/a.out'  -G V4.1.2  -T SG4  -M IA32  '-Wl,$(AS_SYSTEM_PATH)/E0434/SG4/IA32/libDRV_mbus.a' '-Wl,$(AS_TEMP_PATH)/Archives/$(AS_CONFIGURATION)/$(AS_PLC)/libbecome.a' '-Wl,$(AS_SYSTEM_PATH)/E0434/SG4/IA32/libstandard.a' '-Wl,$(AS_SYSTEM_PATH)/E0434/SG4/IA32/libDataObj.a' '-Wl,$(AS_SYSTEM_PATH)/E0434/SG4/IA32/libdvframe.a' '-Wl,$(AS_SYSTEM_PATH)/E0434/SG4/IA32/libAsBrStr.a' '-Wl,$(AS_SYSTEM_PATH)/E0434/SG4/IA32/libasstring.a' '-Wl,$(AS_SYSTEM_PATH)/E0434/SG4/IA32/libAsIecCon.a' '-Wl,$(AS_SYSTEM_PATH)/E0434/SG4/IA32/libastime.a' '-Wl,$(AS_SYSTEM_PATH)/E0434/SG4/IA32/libruntime.a' '-Wl,$(AS_SYSTEM_PATH)/E0434/SG4/IA32/liboperator.a' -specs=I386specs_brelf -secret '$(AS_PROJECT_PATH)_br.as.ccompiler.exe'

$(AS_CPU_PATH)/Program1/Cyclic.c.o: \
	$(AS_PROJECT_PATH)/Logical/Program1/Cyclic.c \
	$(AS_PROJECT_PATH)/Logical/Libraries/become/become.fun \
	$(AS_PROJECT_PATH)/Logical/Libraries/become/Types.typ \
	$(AS_PROJECT_PATH)/Logical/Libraries/standard/standard.fun \
	$(AS_PROJECT_PATH)/Logical/Program1/Variables.var \
	$(AS_PROJECT_PATH)/Logical/Global.var \
	$(AS_PROJECT_PATH)/Logical/Global.typ
	@'$(AS_BIN_PATH)/BR.AS.CCompiler.exe' '$(AS_PROJECT_PATH)/Logical/Program1/Cyclic.c' -o '$(AS_CPU_PATH)/Program1/Cyclic.c.o'  -T SG4  -M IA32  -B E4.34 -G V4.1.2  -s 'Program1' -t '$(AS_TEMP_PATH)' -specs=I386specs_brelf -I '$(AS_PROJECT_PATH)/Logical/Program1' '$(AS_TEMP_PATH)/Includes/Program1' '$(AS_TEMP_PATH)/Includes' -trigraphs -fno-asm -D _DEFAULT_INCLUDES -D _SG4 -fPIC -O0 -g -Wall -include '$(AS_CPU_PATH)/Libraries.h' -x c -P '$(AS_PROJECT_PATH)' -secret '$(AS_PROJECT_PATH)_br.as.ccompiler.exe'

$(AS_CPU_PATH)/Program1/Init.c.o: \
	$(AS_PROJECT_PATH)/Logical/Program1/Init.c \
	$(AS_PROJECT_PATH)/Logical/Libraries/become/become.fun \
	$(AS_PROJECT_PATH)/Logical/Libraries/become/Types.typ \
	$(AS_PROJECT_PATH)/Logical/Libraries/standard/standard.fun \
	$(AS_PROJECT_PATH)/Logical/Program1/Variables.var \
	$(AS_PROJECT_PATH)/Logical/Global.var \
	$(AS_PROJECT_PATH)/Logical/Global.typ
	@'$(AS_BIN_PATH)/BR.AS.CCompiler.exe' '$(AS_PROJECT_PATH)/Logical/Program1/Init.c' -o '$(AS_CPU_PATH)/Program1/Init.c.o'  -T SG4  -M IA32  -B E4.34 -G V4.1.2  -s 'Program1' -t '$(AS_TEMP_PATH)' -specs=I386specs_brelf -I '$(AS_PROJECT_PATH)/Logical/Program1' '$(AS_TEMP_PATH)/Includes/Program1' '$(AS_TEMP_PATH)/Includes' -trigraphs -fno-asm -D _DEFAULT_INCLUDES -D _SG4 -fPIC -O0 -g -Wall -include '$(AS_CPU_PATH)/Libraries.h' -x c -P '$(AS_PROJECT_PATH)' -secret '$(AS_PROJECT_PATH)_br.as.ccompiler.exe'

$(AS_CPU_PATH)/Program1/Exit.c.o: \
	$(AS_PROJECT_PATH)/Logical/Program1/Exit.c \
	$(AS_PROJECT_PATH)/Logical/Libraries/become/become.fun \
	$(AS_PROJECT_PATH)/Logical/Libraries/become/Types.typ \
	$(AS_PROJECT_PATH)/Logical/Libraries/standard/standard.fun \
	$(AS_PROJECT_PATH)/Logical/Program1/Variables.var \
	$(AS_PROJECT_PATH)/Logical/Global.var \
	$(AS_PROJECT_PATH)/Logical/Global.typ
	@'$(AS_BIN_PATH)/BR.AS.CCompiler.exe' '$(AS_PROJECT_PATH)/Logical/Program1/Exit.c' -o '$(AS_CPU_PATH)/Program1/Exit.c.o'  -T SG4  -M IA32  -B E4.34 -G V4.1.2  -s 'Program1' -t '$(AS_TEMP_PATH)' -specs=I386specs_brelf -I '$(AS_PROJECT_PATH)/Logical/Program1' '$(AS_TEMP_PATH)/Includes/Program1' '$(AS_TEMP_PATH)/Includes' -trigraphs -fno-asm -D _DEFAULT_INCLUDES -D _SG4 -fPIC -O0 -g -Wall -include '$(AS_CPU_PATH)/Libraries.h' -x c -P '$(AS_PROJECT_PATH)' -secret '$(AS_PROJECT_PATH)_br.as.ccompiler.exe'

$(AS_CPU_PATH)/Program1/_bur_pvdef.c.o: \
	$(AS_PROJECT_PATH)/Logical/Libraries/become/become.fun \
	$(AS_PROJECT_PATH)/Logical/Libraries/become/Types.typ \
	$(AS_PROJECT_PATH)/Logical/Libraries/standard/standard.fun \
	$(AS_PROJECT_PATH)/Logical/Program1/Variables.var \
	$(AS_PROJECT_PATH)/Logical/Global.var \
	$(AS_PROJECT_PATH)/Logical/Global.typ
	@'$(AS_BIN_PATH)/BR.AS.CCompiler.exe' '$(AS_PATH)/AS/GnuInst/V4.1.2/i386-elf/include/bur/_bur_pvdef.c' -o '$(AS_CPU_PATH)/Program1/_bur_pvdef.c.o'  -T SG4  -M IA32  -B E4.34 -G V4.1.2  -s 'Program1' -t '$(AS_TEMP_PATH)' -specs=I386specs_brelf -I '$(AS_PROJECT_PATH)/Logical/Program1' '$(AS_TEMP_PATH)/Includes/Program1' '$(AS_TEMP_PATH)/Includes' -trigraphs -fno-asm -D _DEFAULT_INCLUDES -D _SG4 -fPIC -O0 -g -Wall -include '$(AS_CPU_PATH)/Libraries.h' -P '$(AS_PROJECT_PATH)' 
 -secret '$(AS_PROJECT_PATH)_br.as.ccompiler.exe'

-include $(AS_CPU_PATH)/Force.mak 

