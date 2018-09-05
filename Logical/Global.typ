
TYPE
	Pump_typ : 	STRUCT 
		status_running : BOOL; (*������ ������ "������� / ��������"*)
		status_remote : BOOL; (*������ ������������� "�������������"*)
		cmd_on : BOOL; (*������� "��������" �����*)
		button_stop : BOOL; (*������ "����"*)
	END_STRUCT;
	Valve_typ : 	STRUCT 
		status_remote : BOOL; (*������ ������������� "�������������"*)
		status_local : BOOL; (*������ ������������� "�������"*)
		button_open : BOOL; (*������ "�������" ��������*)
		button_close : BOOL; (*������ "�������" ��������*)
		button_stop : BOOL; (*������ "����" ��������*)
		signal_valve_opened : BOOL; (*������ �� ��������� "�������� �������"*)
		signal_valve_closed : BOOL; (*������ �� ��������� "�������� �������"*)
		cmd_valve_open : BOOL; (*������� ������� ��������*)
		cmd_valve_close : BOOL; (*������� ������� ��������*)
		feedback : Analog_FB; (*��������� �������� (0-100%)*)
	END_STRUCT;
	Tank_typ : 	STRUCT 
		level : Analog_FB; (*������� �������� � ����������*)
	END_STRUCT;
END_TYPE
