
TYPE
	DRVmbus_typ : 	STRUCT 
		EventPV1 : BOOL;
		EventPV4 : BOOL;
		EventPV5 : BOOL;
		EventPV41 : BOOL;
		EventPV16 : BOOL;
		EventPV50 : BOOL;
		EventPV51 : BOOL;
		EventPV52 : BOOL;
		EventPV53 : BOOL;
		EventPV54 : BOOL;
		EventPV55 : BOOL;
		EventPV56 : BOOL;
		LocalPV1 : ARRAY[0..27]OF BOOL;
		LocalPV4 : ARRAY[0..10]OF UINT;
		LocalPV5 : BOOL;
		LocalPV41 : ARRAY[0..10]OF UINT;
		LocalPV16 : ARRAY[0..12]OF UINT;
		LocalPV50 : BOOL;
		LocalPV51 : BOOL;
		LocalPV52 : BOOL;
		LocalPV53 : BOOL;
		LocalPV54 : BOOL;
		LocalPV55 : BOOL;
		LocalPV56 : BOOL;
	END_STRUCT;
END_TYPE
