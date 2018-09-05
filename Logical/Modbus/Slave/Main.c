#include <bur/plctypes.h>
#include <string.h>
#include "become.h"
#include <drv_mbus.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

_LOCAL UDINT ident;
_LOCAL BOOL fSlave, openFailed;
_LOCAL UDINT adr;
_LOCAL USINT i, j;

void _INIT ProgramInit(void)
{	
	adr = (UDINT) strcpy(device, "IF1");
	adr = (UDINT) strcpy(mode, "/PHY=RS232 /PA=N /DB=8 /SB=1 /BD=19200");
	
	SOpen.enable = 1;
	SOpen.pDevice = (UDINT) &device;
	SOpen.pMode = (UDINT) &mode;
	SOpen.own_ID = 01;
	SOpen.timeout = 500;
	MBSOpen(&SOpen);
		
	Slave.ident = SOpen.ident;
	
	if (!SOpen.status){
		ident = SOpen.ident;
		fSlave = 1;
		openFailed = 0;
	}
	else{
		fSlave = 0;
		openFailed = 1;
	}
	
	/* Верхняя шкала датчика */
	adr = (UDINT) memcpy (&MB4[2],&TANK.level.sett.scale_h, sizeof(TANK.level.sett.scale_h));	// [2,3]
	/* Нижняя шкала датчика */
	adr = (UDINT) memcpy (&MB4[4],&TANK.level.sett.scale_l, sizeof(TANK.level.sett.scale_l));	// [4,5]
	/* Таймер задвижки */
	MB4[6] = timer_for_valve;																	// [6]
	/* Верхняя уставка */
	adr = (UDINT) memcpy (&MB4[7],&level_limits.Hi, sizeof(level_limits.Hi));					// [7,8]
	/* Нижняя уставка */
	adr = (UDINT) memcpy (&MB4[9],&level_limits.Lo, sizeof(level_limits.Lo));					// [9,10]
}

void _CYCLIC ProgramCyclic(void)
{
	// !openFailed && fSlave
	if (!openFailed && fSlave){ 
		
		Slave.enable = 1;
		MBSlave(&Slave);
		
		/* Уровень воды в резервуаре */
		adr = (UDINT) memcpy (&MB4[0],&TANK.level.value, sizeof(TANK.level.value));                 // [0,1]

		/* Задание верхней шкалы*/
		adr = (UDINT) memcpy (&TANK.level.sett.scale_h, &MB4[2], sizeof(TANK.level.sett.scale_h));	// [2,3]
		/* Задание нижней шкалы*/
		adr = (UDINT) memcpy (&TANK.level.sett.scale_l, &MB4[4], sizeof(TANK.level.sett.scale_l));	// [4,5]
		/* Задание времени открывания задвижки */
		timer_for_valve = MB4[6];																	// [6]
		/* Задание верхней уставки*/
		adr = (UDINT) memcpy (&level_limits.Hi, &MB4[7], sizeof(level_limits.Hi));					// [7,8]
		/* Задание нижней уставки*/
		adr = (UDINT) memcpy (&level_limits.Lo, &MB4[9], sizeof(level_limits.Lo));					// [9,10]
		
		if (MB0[28]){
			alarm[0] = 0;
			alarm[1] = 0;
			alarm[2] = 0;
			alarm[3] = 0;
			alarm[4] = 0;
			alarm[5] = 0;
			alarm[6] = 0;
			alarm[7] = 0;
		}
	
		/* Задвижка открыта */
		MB0[0] = VALVE.signal_valve_opened;		// [0] Coil
		/* Задвижка закрыта */
		MB0[1] =  VALVE.signal_valve_closed;	// [1] Coil
		/* Задвижка в дистанционном режиме */
		MB0[2] = VALVE.status_remote;			// [2] Coil	
		/* Задвижка в местном режиме */
		MB0[3] = VALVE.status_local;			// [3] Coil
		/* Насос в дистанционном режиме */
		MB0[4] = PUMP.status_remote;			// [4] Coil
		/* Насос в работе */
		MB0[5] = PUMP.status_running;			// [5] Coil	
		
		for ( i = 0, j = 6 ; i <= 7; i++){
			MB0[j] = alarm[i];					// [6] [7] [8] [9] [10] [11] [12] [13] Coils
			j++;
		}
		
		/* Включить режим "Автомат" */
		mode_remote_auto = MB0[21];				// [21] Coil
		/* Включить режим "Manual" */
		mode_remote_manual = MB0[22];			// [22] Coil
		/* Открытие задвижки */
		cmd_valve_open = MB0[23];				// [23] Coil
		/* Закрытие задвижки */
		cmd_valve_close = MB0[24];				// [24] Coil
		/* Останов задвижки */
		cmd_valve_stop = MB0[25];				// [25] Coil
		/* Запуск насоса */
		cmd_pump_on = MB0[26];					// [26] Coil
		/* Останов насоса */
		cmd_pump_off = MB0[27];					// [27] Coil
	}
}

void _EXIT ProgramExit(void)
{

}

