$(AS_CPU_PATH)/ashwac.br: \
	FORCE \
	$(AS_PROJECT_CONFIG_PATH)/Hardware.hw 
	@'$(AS_BIN_PATH)/BR.AS.SystemConfiguration.Builder.exe' '$(AS_PROJECT_CONFIG_PATH)/Hardware.hw'  -L 'AsBrStr: V*, AsIecCon: V*, asstring: V*, astime: V*, become: V1.00.0, DataObj: V*, DRV_mbus: V*, dvframe: V*, operator: V*, runtime: V*, standard: V*' -c '$(AS_CONFIGURATION)' -Z 'Acp10Arnc0: 3.18.2, mapp: 1.62.1, UnitSystem: n.d, TextSystem: n.d, Connectivity: n.d, AAS: n.d' -o '$(AS_CPU_PATH)/ashwac.br' -T SG4  -M IA32  -B E4.34 -P '$(AS_PROJECT_PATH)' -s 'Config1' -secret '$(AS_PROJECT_PATH)_br.as.systemconfiguration.builder.exe'

FORCE:

-include $(AS_CPU_PATH)/Force.mak 
