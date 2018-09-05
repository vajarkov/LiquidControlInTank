#include <bur/plctypes.h>
#include <string.h>
#include "become.h"

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

_LOCAL UDINT ident;
_LOCAL BOOL fMaster, openfailed;
_LOCAL BOOL blockRead, firstInit;
_LOCAL UDINT adr;
_LOCAL USINT i, j;

void _INIT ProgramInit(void)
{
	/* Внутренние переменные для разовой инициализации технологических параметров на панели */
	blockRead = 1;
	firstInit = 1;
			
	Master.MBMOpen.enable = 1;
	Master.MBMOpen.pDevice = (UDINT) &device;
	Master.MBMOpen.pMode = (UDINT) &mode;
	Master.MBMOpen.pConfig = (UDINT) &config;
	Master.MBMOpen.timeout = 2000;
	Master.MBMOpen.ascii = 0;
	MBMOpen(&Master.MBMOpen);
	
	if (!Master.MBMOpen.status){
		ident = Master.MBMOpen.ident;
		fMaster = 1;
		openfailed = 0;
	}else{
		fMaster = 0;
		openfailed = 1;
	}	
}

void _CYCLIC ProgramCyclic(void)
{
	/* Блокировка кнопок управления задвижкой и насосом, если не выбран режим "Ручной"*/
	if (!mode_remote_manual){
		block_pump_cmd = 1;
		block_valve_cmd = 1;
	}else {
		block_pump_cmd = 0;
		block_valve_cmd = 0;
	}
		
	/* Если насос и задвижка не в дистанционном режиме, то блокируются кнопки выбора режима "Автомат" либо "Ручное" на Touch-панели */
	if (!PUMP.status_remote || !VALVE.status_remote){
		block_auto = 1;
		//block_manual = 1;
	}else{
		block_auto = 0;
		//block_manual = 0;
	}
	
	/* Если насос и задвижка в дистанционном режиме, то при нажатии на кнопку "Автомат" на Touch-панели блокируется кнопка "Ручное", и наоборот */	
	if (PUMP.status_remote && VALVE.status_remote){
		block_manual = mode_remote_auto ? 1 : 0;
		block_auto = mode_remote_manual ? 1 : 0;
	}
	
	if (!openfailed && fMaster){
		Master.MBMaster.enable = 1;
		Master.MBMaster.ident = ident;
		MBMaster(&Master.MBMaster);
	}
	
	DRVmbus.EventPV4 = 1;
	DRVmbus.EventPV1 = 1;
		
	/* Уровень воды в резервуаре */
	adr = (UDINT) memcpy(&TANK.level.value, &DRVmbus.LocalPV4[0], sizeof(TANK.level.value));						//[0,1] Holding

	/* Запись параметров будет просиходить по нажатию на кнопку */
	if (Cmd_Write){
		
		/* Задание верхней шкалы*/
		adr = (UDINT) memcpy(&DRVmbus.LocalPV16[0], &TANK.level.sett.scale_h, sizeof(TANK.level.sett.scale_h));	//[2,3] Holding
		/* Задание нижней шкалы*/
		adr = (UDINT) memcpy(&DRVmbus.LocalPV16[2], &TANK.level.sett.scale_l, sizeof(TANK.level.sett.scale_l));	//[4,5] Holding
		/* Задание времени открывания задвижки */
		DRVmbus.LocalPV16[4] = timer_for_valve; 																//[6]   Holding
		/* Задание верхней уставки*/
		adr = (UDINT) memcpy(&DRVmbus.LocalPV16[5], &level_limits.Hi, sizeof(level_limits.Hi));					//[7,8] Holding
		/* Задание нижней уставки*/
		adr = (UDINT) memcpy(&DRVmbus.LocalPV16[7], &level_limits.Lo, sizeof(level_limits.Lo));					//[9,10] Holding			
		
		if(!DRVmbus.EventPV16){
			DRVmbus.EventPV16 = 1;
			Cmd_Write = 0;
		}
		
	}
	/* Считывание параметров со Slave один раз при запуске панели */
	if (firstInit){
		
		if (!DRVmbus.EventPV41){
			
			DRVmbus.EventPV41 = 1;
			//DRVmbus.EventPV41 = 0;
			firstInit = 0;			// Переменная для блокировки считывания параметров только один раз
		}
	}
	else{
		if (!DRVmbus.EventPV41 && blockRead){
			/* Верхняя шкала датчика */
			adr = (UDINT) memcpy(&TANK.level.sett.scale_h, &DRVmbus.LocalPV41[0], sizeof(TANK.level.sett.scale_h));	//[2,3] Holding
			/* Задание нижней шкалы */
			adr = (UDINT) memcpy(&TANK.level.sett.scale_l, &DRVmbus.LocalPV41[2], sizeof(TANK.level.sett.scale_l));	//[4,5] Holding
			/* Задание времени открывания задвижки */
			timer_for_valve = DRVmbus.LocalPV41[4]; 																//[6]   Holding
			/* Задание верхней уставки */
			adr = (UDINT) memcpy(&level_limits.Hi, &DRVmbus.LocalPV41[5], sizeof(level_limits.Hi));					//[7,8] Holding
			/* Задание нижней уставки */
			adr = (UDINT) memcpy(&level_limits.Lo, &DRVmbus.LocalPV41[7], sizeof(level_limits.Lo));					//[9,10] Holding
			
			blockRead = 0;
		}
	}
		
	/* Задвижка открыта */
	VALVE.signal_valve_opened = DRVmbus.LocalPV1[0];	// [0] Coil
	/* Задвижка закрыта */
	VALVE.signal_valve_closed = DRVmbus.LocalPV1[1];	// [1] Coil
	/* Задвижка в дистанционном режиме */
	VALVE.status_remote = DRVmbus.LocalPV1[2];			// [2] Coil	
	/* Задвижка в местном режиме */
	VALVE.status_local = DRVmbus.LocalPV1[3];			// [3] Coil
	/* Насос в дистанционном режиме */
	PUMP.status_remote = DRVmbus.LocalPV1[4];			// [4] Coil
	/* Насос в работе */
	PUMP.status_running = DRVmbus.LocalPV1[5];			// [5] Coil	
		
	for ( i = 0, j = 6 ; i <= 7; i++){
		alarm[i] = DRVmbus.LocalPV1[j];					// [6] [7] [8] [9] [10] [11] [12] [13] Coils
		j++;
	}	
	
	/* Сброс всех алармов с панели */
	if (ack_alarms){
		
		if (!DRVmbus.EventPV5){
			DRVmbus.LocalPV5 = ack_alarms;
			DRVmbus.EventPV5 = 1;
			ack_alarms = 0;
		}
	}
	if (DRVmbus.LocalPV5){
		if (!DRVmbus.EventPV5){
			DRVmbus.LocalPV5 = 0;
			DRVmbus.EventPV5 = 1;
		}
	}
		
	/* Если считываемый сигнал "Режим Автомат" отличается от записываемого*/
	if (DRVmbus.LocalPV1[14] != mode_remote_auto){
			
		/* Если нет алармов, то разрешение на запись */
		if ((alarm[0] != 1) && (alarm[1] != 1) && (alarm[2] != 1) && (alarm[3] != 1) && (alarm[4] != 1) && (alarm[7] != 1)){
			if (!DRVmbus.EventPV50){
				DRVmbus.LocalPV50 = mode_remote_auto;					// [21] Coil
				DRVmbus.EventPV50 = 1;
			}
		}
		else{
			/* Если есть алармы, то присваиваем счиытваемое значение */
			mode_remote_auto = DRVmbus.LocalPV1[14];		// [14] Coil
			if (!DRVmbus.EventPV50){
				DRVmbus.LocalPV50 = mode_remote_auto;					// [21] Coil
				DRVmbus.EventPV50 = 1;
			}
		}
	}
	if ((DRVmbus.LocalPV1[14] == 0) && (mode_remote_auto == 0)){
		if (!DRVmbus.EventPV50){
			DRVmbus.LocalPV50 = 0;					// [21] Coil
			DRVmbus.EventPV50 = 1;
		}
	}
	
	/* Если считываемый сигнал "Режим Manual" отличается от записываемого*/	
	if (DRVmbus.LocalPV1[15] != mode_remote_manual){
		
		/* Если нет алармов, то разрешение на запись */
		if ((alarm[0] != 1) && (alarm[1] != 1) && (alarm[2] != 1) && (alarm[3] != 1) && (alarm[4] != 1) && (alarm[7] != 1)){
			if (!DRVmbus.EventPV51){
				DRVmbus.LocalPV51 = mode_remote_manual;					// [22] Coil
				DRVmbus.EventPV51 = 1;
			}
		}
		else{			
			if (!DRVmbus.EventPV51){
				mode_remote_manual = DRVmbus.LocalPV1[15];		// [15] Coil
				DRVmbus.LocalPV51 = mode_remote_manual;					// [22] Coil
				DRVmbus.EventPV51 = 1;
			}
		}
	}
	if ((DRVmbus.LocalPV1[15] == 0) && (mode_remote_manual == 0)){
		if (!DRVmbus.EventPV51){
			DRVmbus.LocalPV51 = 0;					// [22] Coil
			DRVmbus.EventPV51 = 1;
		}
	}
	
	/* Если считываемый сигнал "Openvalve" отличается от записываемого */
	if (DRVmbus.LocalPV1[16] != cmd_valve_open){
	
		/* Если нет алармов и задвижка не в открытом положении, то разрешение на запись команды открыть задвижку */
		if ((alarm[1] != 1) && (alarm[4] != 1) && !VALVE.signal_valve_opened){
			if (!DRVmbus.EventPV52){
				DRVmbus.LocalPV52 = cmd_valve_open;						// [23] Coil
				DRVmbus.LocalPV53 = 0;
				DRVmbus.EventPV52 = 1;
				DRVmbus.EventPV53 = 1;
			}
		}
		/* Если аларм и задвижка не открыта, либо нет алармов и задвижка открыта, то обнуляем команду */
		if (((alarm[1] || alarm[4]) && !VALVE.signal_valve_opened) || ((alarm[1] != 1) && (alarm[4] != 1) && VALVE.signal_valve_opened)){			
			if (!DRVmbus.EventPV52){
				cmd_valve_open = 0;
				DRVmbus.LocalPV52 = cmd_valve_open;						// [23] Coil
				DRVmbus.EventPV52 = 1;
			}
		}
	}
	
	/* Если считываемый сигнал "Close valve" отличается от записываемого */
	if (DRVmbus.LocalPV1[17] != cmd_valve_close){
	
		/* Если нет алармов и задвижка не в закрытом положении, то разрешение на запись команды закрыть задвижку */
		if ((alarm[3] != 1) && (alarm[4] != 1) && !VALVE.signal_valve_closed){
			if (!DRVmbus.EventPV53){
				DRVmbus.LocalPV53 = cmd_valve_close;					// [24] Coil
				DRVmbus.LocalPV52 = 0;
				DRVmbus.EventPV53 = 1;
				DRVmbus.EventPV52 = 1;
			}
		}
		/* Если алармы и задвижка не закрыта, либо алармов нет и закрыта задвижка, то следует обнуление команды */
		if (((alarm[3] || alarm[4]) && !VALVE.signal_valve_closed) || ((alarm[3] != 1) && (alarm[4] != 1) && VALVE.signal_valve_closed)){			
			if (!DRVmbus.EventPV53){
				cmd_valve_close = 0;
				DRVmbus.LocalPV53 = cmd_valve_close;					// [24] Coil
				DRVmbus.EventPV53 = 1;
			}
		}
	}
	
	/* Если считываемый сигнал "Stop valve" отличается от записываемого */
	if (cmd_valve_stop){
		if (!DRVmbus.EventPV54 && !DRVmbus.LocalPV54){
			DRVmbus.LocalPV54 = cmd_valve_stop;						// [25] Coil
			DRVmbus.LocalPV52 = 0;
			DRVmbus.LocalPV53 = 0;
			DRVmbus.EventPV54 = 1;
			DRVmbus.EventPV52 = 1;
			DRVmbus.EventPV53 = 1;
			cmd_valve_stop = 0;
			cmd_valve_open = 0;
			cmd_valve_close = 0;
		}
	}
	if (DRVmbus.LocalPV54){
		if (!DRVmbus.EventPV54){

			DRVmbus.LocalPV54 = 0;
			DRVmbus.EventPV54 = 1;
		}
	}
	
	/* Если считываемый сигнал "Run pump" отличается от записываемого */
	if (DRVmbus.LocalPV1[19] != cmd_pump_on){
		/* Если нет алармов и насос не в работе, то разрешение на запись запуска насоса */
		if ((alarm[0] != 1) && (alarm[7] != 1) && !PUMP.status_running){
			if (!DRVmbus.EventPV55){
				DRVmbus.LocalPV55 = cmd_pump_on;						// [26] Coil
				DRVmbus.EventPV55 = 1;
			}
		}
		/* Если есть аларм и насос не запустился, либо алармов нет и насос запустился, то обнуляем команду */
		if(((alarm[0] || alarm[7]) && !PUMP.status_running) || ((alarm[0] != 1) && (alarm[7] != 1) && PUMP.status_running)){
			if(!DRVmbus.EventPV55){
				cmd_pump_on = 0;
				DRVmbus.LocalPV55 = cmd_pump_on;
				DRVmbus.EventPV55 = 1;
			}
		}
	}
	
	/* Если считываемый сигнал "остановить насос" отличается от записываемого */
	if (DRVmbus.LocalPV1[20] != cmd_pump_off){
		/* Если нет алармов и насоса в работе, то разрешение на запись останова насоса */
		if ((alarm[2] != 1) && PUMP.status_running){
			if (!DRVmbus.EventPV56){
				DRVmbus.LocalPV56 = cmd_pump_off;						// [27] Coil
				DRVmbus.EventPV56 = 1;
			}
		}
		/* Если есть аларм и насос не выключился, то обнуляем команду */
		if((alarm[2] && PUMP.status_running) || ((alarm[2] == 0) && !PUMP.status_running)){
			if(!DRVmbus.EventPV56){
				cmd_pump_off = 0;
				DRVmbus.LocalPV56 = cmd_pump_off;
				DRVmbus.EventPV56 = 1;
			}
		}
	}
}
void _EXIT ProgramExit(void)
{
	DRVmbus.EventPV1 = 0;
	DRVmbus.EventPV4 = 0;
	DRVmbus.EventPV5 = 0;
	DRVmbus.EventPV16 = 0;
	DRVmbus.EventPV41 = 0;
	DRVmbus.EventPV50 = 0;
	DRVmbus.EventPV51 = 0;
	DRVmbus.EventPV52 = 0;
	DRVmbus.EventPV53 = 0;
	DRVmbus.EventPV54 = 0;
	DRVmbus.EventPV55 = 0;
	DRVmbus.EventPV56 = 0;
}



