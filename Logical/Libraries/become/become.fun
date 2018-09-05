
FUNCTION_BLOCK Analog_FB (*���������� ������*)
	VAR_INPUT
		raw : INT; (*"�����" �������� � ������*)
		ai_input_status : BYTE; (*����-������ � ������*)
		ai_channel_num : BYTE; (*����� ����������� �����*)
	END_VAR
	VAR_OUTPUT
		value : REAL; (*����������������� �������� � ���������� ��������*)
	END_VAR
	VAR
		sett : Analog_Settings_type;
		limits : Analog_Limits_typ;
		alarms : anaAlarmsEnum;
	END_VAR
	VAR_INPUT
		adc_up : INT; (*������� �����*)
		adc_dn : INT; (*������ �����*)
	END_VAR
END_FUNCTION_BLOCK
