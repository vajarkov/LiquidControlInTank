
TYPE
	Master_typ : 	STRUCT 
		MBMOpen : MBMOpen;
		MBMaster : MBMaster;
		MBMClose : MBMClose;
		MBMCmd : MBMCmd;
		S1 : BOOL; (*command to start sending*)
		S2 : BOOL; (*command to start the MBMClose FUB*)
	END_STRUCT;
END_TYPE
