UnmarkedObjectFolder := C:/projects/LiquidControlInTank/Logical/Modbus/datamod
MarkedObjectFolder := C:/projects/LiquidControlInTank/Logical/Modbus/datamod

$(AS_CPU_PATH)/datamod.br: \
	$(AS_PROJECT_PATH)/Logical/Modbus/datamod/datamod.dat \
 	FORCE 
	@'$(AS_BIN_PATH)/BR.AS.DataObjectBuilder.exe'   '$(AS_PROJECT_PATH)/Logical/Modbus/datamod/datamod.dat' -o '$(AS_CPU_PATH)/datamod.br' -T SG4  -B E4.34 -v V1.00.0 -s 'Modbus.datamod'

FORCE: