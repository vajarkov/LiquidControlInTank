$(AS_CPU_PATH)/asfw.br: \
	$(AS_PROJECT_CONFIG_PATH)/Hardware.hw \
	$(AS_INSTALL_PATH)/Upgrades/Modified.txt
	@'$(AS_BIN_PATH)/BR.AS.ConfigurationBuilder.exe'  '$(AS_PROJECT_CONFIG_PATH)/Hardware.hw' -v V1.00.0 -S 'X20cCP1301' -o '$(AS_CPU_PATH)/asfw.br' -T SG4 -B E4.34 -P '$(AS_PROJECT_PATH)' -c '$(AS_CONFIGURATION)' -zip -s X20cCP1301 -firmware -secret '$(AS_PROJECT_PATH)_br.as.configurationbuilder.exe'

