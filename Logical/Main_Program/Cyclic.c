#include <bur/plc.h>
#include <bur/plctypes.h>
#include <standard.h>
#include <become.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

_LOCAL BOOL pump_status_changed, pump_prev_status;

/* 	alarm[0] - Авария запуска насоса;
	alarm[1] - Авария открытия задвижки;
	alarm[2] - Авария выключения насоса;
	alarm[3] - Авария закрытия задвижки;
	alarm[4] - Сработала кнопка останова задвижки;
	alarm[5] - Верхний уровень в резервуаре;
	alarm[6] - Нижний уровень в резервуаре;
	alarm[7] - Сработала кнопка останова насоса*/

BOOL TimerValve_func(BOOL start, INT presetTime){
	
	/* Таймер умножаем на 1000 (равно 1 секунде) */
	TON_valve.IN = start;
	TON_valve.PT = presetTime * 1000;
	TON(&TON_valve);
	
	return TON_valve.Q;
}

BOOL TimerPump_func(BOOL start, INT presetTime){
	
	/* Таймер умножаем на 1000 (равно 1 секунде) */
	TON_pump.IN = start;
	TON_pump.PT = presetTime * 1000;
	TON(&TON_pump);
	
	return TON_pump.Q;
}

void Alarm_func(){
	
	/* Вержний уровень в резервуаре */
	if (TANK.level.value >= TANK.level.limits.HiHi){
		alarm[5] = 1; 
		alarm[6] = 0;
	}
	/* Нижний уровень в резервуаре */
	if(TANK.level.value <= TANK.level.limits.LoLo){
		alarm[6] = 1;
		alarm[5] = 0;
	}
	/* Если уровень в пределах нормы, то сбросить алармы по уровню */
	if ((TANK.level.value > TANK.level.limits.LoLo) && (TANK.level.value < TANK.level.limits.HiHi)){
		alarm[5] = 0;
		alarm[6] = 0;
	}
	if (alarm[0] || alarm[7] || alarm[2]){
		PUMP.cmd_on = 0;
	}
	if (alarm[0]){
		cmd_pump_on = 0;
	}
	if (alarm[2]) {
		cmd_pump_off = 0;
	}
	if (alarm[1] || alarm[4]){
		VALVE.cmd_valve_open = 0;
		cmd_valve_open = 0;
	}
	if (alarm[3] || alarm[4]){
		VALVE.cmd_valve_close = 0;
		cmd_valve_close = 0;
	}
	if (alarm[0] || alarm[1] || alarm[2] || alarm[3]){
		mode_remote_manual = 0;
	}
	if (alarm[0] || alarm[1] || alarm[2] || alarm[3] || alarm[4] || alarm[7]){
		mode_remote_auto = 0;}
}

void _CYCLIC ProgramCyclic(void){
	
	Alarm_func();
	/* =========================== */
	VALVE.feedback.adc_up = 32767;
	VALVE.feedback.adc_dn = 0;
	Analog_FB(&VALVE.feedback);
	/* =========================== */
	TANK.level.adc_up = 11000;
	TANK.level.adc_dn = 0;
	Analog_FB(&TANK.level);
	
	/* Мониторинг состояния задвижки */
	VALVE.signal_valve_opened = (VALVE.feedback.value == 100) ? 1 : 0;
	VALVE.signal_valve_closed = (VALVE.feedback.value == 0) ? 1 : 0;
	
	/* Если насос и задвижка в дистанционном режиме, то разрешение на их запуск с панели" */
	if (PUMP.status_remote || VALVE.status_remote){
				
		/* При нажатии кнопки "Стоп" запустить триггер */
		if (!VALVE.button_stop){
			mode_remote_auto = 0;
			mode_remote_manual = 0;
			VALVE.cmd_valve_close = 0;
			VALVE.cmd_valve_open = 0;
			cmd_valve_close = 0;
			cmd_valve_open = 0;
			TimerPump_func(0, 0);
			TimerValve_func(0, 0);
			alarm[4] = 1; // Сработала кнопка останова задвижки
		}
		
		pump_status_changed = PUMP.status_running ^ pump_prev_status;	// Status is changed
		pump_prev_status = PUMP.status_running;						 	// Previous status of pump
					
		/* При нажатии на кнопку "Стоп" по месту, насос должен остановиться, выйти из всех режимов и обнулить команды */
		if (PUMP.cmd_on && pump_status_changed && (pump_prev_status == 0)){
			PUMP.cmd_on = 0;
			mode_remote_auto = 0;
			mode_remote_manual = 0;
			cmd_pump_on = 0;
			cmd_pump_off = 0;
			alarm[7] = 1;
		}
		
		/* Если на панели выбран режим "Автомат" */
		if (mode_remote_auto){
			
			/* Открытие задвижки и включение насоса по достижению верхней уставки */
			if (TANK.level.value >= level_limits.Hi){
				VALVE.cmd_valve_close = 0;
				VALVE.cmd_valve_open = 1;
			
				/* Если задвижка открылась подаем сигнал на останов насоса */
				if (VALVE.feedback.value == 100){
					TimerValve_func(0, 0);
					VALVE.cmd_valve_open = 0;
					VALVE.signal_valve_opened = 1;					
					PUMP.cmd_on = 1;
					alarm[1] = 0;
					
					/* Насос выключился */
					if (PUMP.status_running){
						TimerPump_func(0, 0);
						alarm[0] = 0;
					}
					
					/* Если насос не включился */
					if (!PUMP.status_running){
						if (TimerPump_func(1, timer_for_pump)){
							PUMP.cmd_on = 0;
							TimerPump_func(0, 0);
							mode_remote_auto = 0;
							MB0[14] = mode_remote_auto;
							alarm[0] = 1;
						}					
					}
				}
				if (VALVE.feedback.value < 100){  /* В течение заданного времени задвижка не открылась*/
					if (TimerValve_func(1, timer_for_valve)){
						VALVE.cmd_valve_open = 0;
						TimerValve_func(0, 0);
						mode_remote_auto = 0;
						MB0[14] = mode_remote_auto;
						alarm[1] = 1;
					}
				}
			}
			
			/* Закрытие задвижки и выключение насоса по достижению нижней уставки */
			if (TANK.level.value <= level_limits.Lo){
				PUMP.cmd_on = 0;
				
				/* Насос выключен - сигнал на закрытие задвижки */
				if (!PUMP.status_running){
					VALVE.cmd_valve_open = 0;
					VALVE.cmd_valve_close = 1;
					TimerPump_func(0, 0);
					alarm[2] = 0;
					
					/* Если задвижка закрылась */
					if (VALVE.feedback.value == 0){
						VALVE.cmd_valve_close = 0;
						VALVE.signal_valve_closed = 1;
						TimerValve_func(0, 0);
						alarm[3] = 0;
					}
					
					/* Если сработал таймер и задвижка не закрылась */
					if (VALVE.feedback.value > 0){
						if (TimerValve_func(1, timer_for_valve)){
							VALVE.cmd_valve_close = 0;
							VALVE.cmd_valve_open = 0;
							TimerValve_func(0, 0);
							mode_remote_auto = 0;
							MB0[14] = mode_remote_auto;
							alarm[3] = 1;
						}
					}
				}
				
				/* Если насос не выключился, то-  */
				if (PUMP.status_running){
					if (TimerPump_func(1, timer_for_pump)){
						PUMP.cmd_on = 0;
						TimerPump_func(0, 0);
						mode_remote_auto = 0;
						MB0[14] = mode_remote_auto;
						alarm[2] = 1;
					}
				}
			}
		}
		
		/* Если на панели выбран режим "Manual" */	
		if (mode_remote_manual){
			
			/* Open valve from Touch panel */
			if (cmd_valve_open){
				VALVE.cmd_valve_close = 0;
				VALVE.cmd_valve_open = 1;
				
				/* Задаем таймер на открытие задвижки */				
				if (VALVE.feedback.value == 100){
					TimerValve_func(0, 0);
					VALVE.cmd_valve_open = 0;
					cmd_valve_open = 0;
					MB0[16] = cmd_valve_open;				// [16] Coil
					VALVE.signal_valve_opened = 1;					
					alarm[1] = 0;
				}
				if (VALVE.feedback.value < 100){
					if (TimerValve_func(1, timer_for_valve)){
						VALVE.cmd_valve_open = 0;
						cmd_valve_open = 0;
						MB0[16] = cmd_valve_open;				// [16] Coil
						TimerValve_func(0, 0);
						mode_remote_manual = 0;
						MB0[15] = mode_remote_manual;
						alarm[1] = 1;
					}
				}
			}
			
			/* Close valve from Touch panel */
			if (cmd_valve_close){
				VALVE.cmd_valve_open = 0;
				VALVE.cmd_valve_close = 1;
				
				/* Задаем таймер на закрытие задвижки */
				if (VALVE.feedback.value == 0){
					TimerValve_func(0, 0);
					VALVE.cmd_valve_close = 0;
					VALVE.signal_valve_closed = 1;					
					cmd_valve_close = 0;
					MB0[17] = cmd_valve_close;				// [17] Coil
					alarm[3] = 0;
				}
				if (VALVE.feedback.value > 0) {
					if(TimerValve_func(1, timer_for_valve)){
						VALVE.cmd_valve_close = 0;
						cmd_valve_close = 0;
						MB0[17] = cmd_valve_close;				
						TimerValve_func(0, 0);
						mode_remote_manual = 0;
						MB0[15] = mode_remote_manual;
						alarm[3] = 1;
					}
				}
			}
			
			/* Turn pump on from Touch panel */
			if (cmd_pump_on){
				PUMP.cmd_on = 1;
				
				if(PUMP.status_running){
					TimerPump_func(0, 0);
					cmd_pump_on = 0;
					MB0[19] = cmd_pump_on;					// [19] Coil
					alarm[0] = 0;
				}
				
				/*Если сработал таймер и насос не включился */
				if (!PUMP.status_running){
					if (TimerPump_func(1, timer_for_pump)){
						PUMP.cmd_on = 0;
						cmd_pump_on = 0;
						MB0[19] = cmd_pump_on;					// [19] Coil
						TimerPump_func(0, 0);
						mode_remote_manual = 0;
						MB0[15] = mode_remote_manual;
						alarm[0] = 1; 
				}
				}
			}
			
			/* Turn pump off from Touch panel */
			if (cmd_pump_off){
				PUMP.cmd_on = 0;
				
				if (!PUMP.status_running){
					TimerPump_func(0, 0);
					cmd_pump_off = 0;
					MB0[20] = cmd_pump_off;					// [20] Coil
					alarm[2] = 0;
				}
				
				/* Если сработал таймер и насос не выключился (залип пускатель и т.п) */
				if (PUMP.status_running){
					if (TimerPump_func(1, timer_for_pump)){ 
						PUMP.cmd_on = 0;
						cmd_pump_off = 0;
						MB0[20] = cmd_pump_off;
						TimerPump_func(0, 0);
						mode_remote_manual = 0;
						MB0[15] = mode_remote_manual;
						alarm[2] = 1;
					}
				}
			}
			
			/* Stop valve from Touch panel */
			if (cmd_valve_stop){
				VALVE.cmd_valve_close = 0;
				VALVE.cmd_valve_open = 0;
				cmd_valve_close = 0;
				cmd_valve_open = 0;
				cmd_valve_stop = 0;
				MB0[18] = cmd_valve_stop;				// [18] Coil
				TimerValve_func (0, 0);
			}
		}
	}
	
	/* Если переключатель режима насоса не в дистанционном */
	if (!PUMP.status_remote)
		PUMP.cmd_on = 0;
	
	/* Если переключатель режима задвижки в положении "0" */
	if (!VALVE.status_local && !VALVE.status_remote){
		VALVE.cmd_valve_open = 0;
		VALVE.cmd_valve_close = 0;
		cmd_valve_close = 0;
		cmd_valve_open = 0;
		mode_remote_auto = 0;
		TimerValve_func(0, 0);
		virtual_valve_close = 0;
		virtual_valve_open = 0;
	}
	
	/* Если переключатель режима задвижки в "Местное"*/
	if (VALVE.status_local){
		
		//mode_remote_auto = 0;
		//cmd_valve_close = 0;
		//cmd_valve_open = 0;
		
		/* Если по месту нажаната кнопка "Открыть" */
		if (VALVE.button_open || virtual_valve_open){
			virtual_valve_open = 1;
			VALVE.cmd_valve_close = 0;
			VALVE.cmd_valve_open = 1;
				
			/* Если сработал таймер и задвижка открылась */
			if (VALVE.feedback.value == 100){
				VALVE.signal_valve_opened = 1;
				VALVE.cmd_valve_open = 0;
				virtual_valve_open = 0;
				TimerValve_func(0, 0);
				alarm[1] = 0;
			}
			
			 /* В течение заданного времени задвижка не открылась*/
			if (VALVE.feedback.value < 100){ 
				if (TimerValve_func(1, timer_for_valve)){
					TimerValve_func(0, 0);
					VALVE.cmd_valve_open = 0;
					virtual_valve_open = 0;
					alarm[1] = 1;      
				}
			}
		}
		
		/* Если по месту нажаната кнопка "Закрыть" */
		if (VALVE.button_close || virtual_valve_close){
			virtual_valve_close = 1;
			VALVE.cmd_valve_open = 0;
			VALVE.cmd_valve_close = 1;			
			
			/* Если сработал таймер и задвижка не закрылась */
			if (VALVE.feedback.value == 0){
				VALVE.signal_valve_closed = 1;
				VALVE.cmd_valve_close = 0;
				virtual_valve_close = 0;
				TimerValve_func(0, 0);
				alarm[3] = 0;
			}
			if (TimerValve_func(1, timer_for_valve) && (VALVE.feedback.value > 0)){
				TimerValve_func(0, 0);
				VALVE.cmd_valve_close = 0;
				virtual_valve_close = 0;
				alarm[3] = 1;
			}
		}
		
		/* Если по месту нажаната кнопка "Стоп" */
		if(!VALVE.button_stop){
			VALVE.cmd_valve_close = 0;
			VALVE.cmd_valve_open = 0;
			TimerPump_func(0,0);
			TimerValve_func(0, 0);
			virtual_valve_close = 0;
			virtual_valve_open = 0;
			alarm[4] = 1; 						// Кнопка "Стоп" по месту
		}
		
	}
}


	
	
