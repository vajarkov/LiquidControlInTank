$(AS_CPU_PATH)/ashwd.br: \
	$(AS_PROJECT_CONFIG_PATH)/Hardware.hw \
	FORCE
	@'$(AS_BIN_PATH)/BR.AS.ConfigurationBuilder.exe'  '$(AS_PROJECT_CONFIG_PATH)/Hardware.hw' -v V1.00.0 -S '4PP065_0571_X74' -o '$(AS_CPU_PATH)/ashwd.br' -T SG4 -B E4.34 -P '$(AS_PROJECT_PATH)' -c '$(AS_CONFIGURATION)' -zip -s 4PP065_0571_X74 -hwd -secret '$(AS_PROJECT_PATH)_br.as.configurationbuilder.exe'


FORCE:
