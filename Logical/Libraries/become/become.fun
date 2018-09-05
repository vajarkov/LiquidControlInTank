
FUNCTION_BLOCK Analog_FB (*Аналоговый сигнал*)
	VAR_INPUT
		raw : INT; (*"сырое" значение с модуля*)
		ai_input_status : BYTE; (*байт-статус с модуля*)
		ai_channel_num : BYTE; (*номер аналогового входа*)
	END_VAR
	VAR_OUTPUT
		value : REAL; (*смасштабированное значение в физических единицах*)
	END_VAR
	VAR
		sett : Analog_Settings_type;
		limits : Analog_Limits_typ;
		alarms : anaAlarmsEnum;
	END_VAR
	VAR_INPUT
		adc_up : INT; (*Верхняя шкала*)
		adc_dn : INT; (*Нижняя шкала*)
	END_VAR
END_FUNCTION_BLOCK
