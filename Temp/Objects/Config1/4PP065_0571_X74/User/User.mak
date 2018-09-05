UnmarkedObjectFolder := C:/projects/LiquidControlInTank/Physical/Config1/4PP065_0571_X74/AccessAndSecurity/UserRoleSystem
MarkedObjectFolder := C:/projects/LiquidControlInTank/Physical/Config1/4PP065_0571_X74/AccessAndSecurity/UserRoleSystem

$(AS_CPU_PATH)/User.br: \
	$(AS_PROJECT_CPU_PATH)/AccessAndSecurity/UserRoleSystem/User.user \
 	FORCE 
	@'$(AS_BIN_PATH)/BR.AS.SystemConfiguration.Builder.exe'   '$(AS_PROJECT_CPU_PATH)/AccessAndSecurity/UserRoleSystem/User.user' -o '$(AS_CPU_PATH)/User.br' -zip -B E4.34 -z n.d -P '$(AS_PROJECT_PATH)' -c '$(AS_CONFIGURATION)' -secret '$(AS_PROJECT_PATH)_br.as.systemconfiguration.builder.exe'

FORCE: