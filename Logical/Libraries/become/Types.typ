(*Аналоговый сигнал*)

TYPE
	Analog_Settings_type : 	STRUCT 
		scale_h : REAL;
		scale_l : REAL;
		offset : REAL;
	END_STRUCT;
	Analog_Limits_typ : 	STRUCT 
		HiHi : REAL;
		Hi : REAL;
		Lo : REAL;
		LoLo : REAL;
		hys : REAL;
	END_STRUCT;
	anaAlarmsEnum : 
		(
		SIGNAL_NO_ALARM := 0,
		SIGNAL_OVER := 1,
		SIGNAL_UNDER := 2,
		SIGNAL_OPEN_LINE := 4,
		SIGNAL_HI_HI := 8,
		SIGNAL_HI := 16,
		SIGNAL_LO := 32,
		SIGNAL_LO_LO := 64
		);
END_TYPE

(*Общие*)

TYPE
	localRemoteSwitchEnum : 
		( (*Положение ключа управления*)
		SW_OFF := 0,
		SW_LOCAL := 1,
		SW_REMOTE := 2
		);
END_TYPE
