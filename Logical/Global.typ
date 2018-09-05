
TYPE
	Pump_typ : 	STRUCT 
		status_running : BOOL; (*Статус насоса "Включен / Выключен"*)
		status_remote : BOOL; (*Статус переключателя "Дистанционный"*)
		cmd_on : BOOL; (*Команда "Включить" насос*)
		button_stop : BOOL; (*Кнопка "Стоп"*)
	END_STRUCT;
	Valve_typ : 	STRUCT 
		status_remote : BOOL; (*Статус переключателя "Дистанционный"*)
		status_local : BOOL; (*Статус переключателя "Местный"*)
		button_open : BOOL; (*Кнопка "Открыть" задвижку*)
		button_close : BOOL; (*Кнопка "Закрыть" задвижку*)
		button_stop : BOOL; (*Кнопка "Стоп" задвижку*)
		signal_valve_opened : BOOL; (*Сигнал на индикацию "Задвижка открыта"*)
		signal_valve_closed : BOOL; (*Сигнал на индикацию "Задвижка закрыта"*)
		cmd_valve_open : BOOL; (*Команда открыть задвижку*)
		cmd_valve_close : BOOL; (*Команда закрыть задвижку*)
		feedback : Analog_FB; (*Состояние задвижки (0-100%)*)
	END_STRUCT;
	Tank_typ : 	STRUCT 
		level : Analog_FB; (*Уровень жидкости в резервуаре*)
	END_STRUCT;
END_TYPE
