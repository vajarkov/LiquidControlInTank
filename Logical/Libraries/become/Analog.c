#include <bur/plctypes.h>
#include "become.h"

void Analog_FB (struct Analog_FB* inst)
{
	INT adc_up = inst->adc_up;
	INT adc_dn = inst->adc_dn;
	REAL raw, phys;
	BOOL signal_fail;
	BYTE status, channel_number;
	anaAlarmsEnum tAlarms = 0;
	
	/* Диагностика состояния аналогового сигнала*/
	/* Нумерация каналов начинается с 0, поэтому "номер канала" - 1. 
	   Статусы каналов разбиты на 2 переменные, поэтому каналы 5-8 
	   заново начинаюся с 0, но во второй переменной */
	
	channel_number = inst->ai_channel_num >4 ? inst->ai_channel_num - 5 : inst->ai_channel_num - 1;
	
	status = (inst->ai_input_status >> (channel_number << 1)) & 0x03;
	
	switch (status)
	{
		case 0x01:
			/* Lower limit */
			tAlarms |= SIGNAL_UNDER;
			//raw = inst->sett.scale_l;
			break;
		case 0x02:
			/* Upper limit */
			tAlarms |= SIGNAL_OVER;
			//raw = inst->sett.scale_h;
			break;
		case 0x03:
			/* Обрыв */
			tAlarms |= SIGNAL_OPEN_LINE;
			//raw = inst->sett.scale_l;
			break;
		default:
			//raw = inst->sett.invert_input_scale ? (32767 - inst->raw) : inst->raw;
			raw = inst->raw;
			//tAlarms = signal_no_alarm;
			break;
	}

	signal_fail = (tAlarms != 0);
	
	/* Представление сигнала в инженерных единицах */ 
	phys = (raw - adc_dn)*(inst->sett.scale_h - inst->sett.scale_l)/(adc_up - adc_dn) + inst->sett.scale_l + inst->sett.offset;
	
	inst->alarms = (inst->alarms & ~(SIGNAL_UNDER | SIGNAL_OVER | SIGNAL_OPEN_LINE)) | tAlarms;
	
	if ((!signal_fail) && (phys >= inst->limits.HiHi))
		inst->alarms |= SIGNAL_HI_HI;
	if ((signal_fail) || (phys < inst->limits.HiHi - inst->limits.hys))
		inst->alarms &= ~SIGNAL_HI_HI;
	
	if ((!signal_fail) && (phys >= inst->limits.Hi))
		inst->alarms |= SIGNAL_HI;
	if ((signal_fail) || (phys < inst->limits.Hi - inst->limits.hys))
		inst->alarms &= ~SIGNAL_HI;
	
	if ((!signal_fail) && (phys <= inst->limits.Lo))
		inst->alarms |= SIGNAL_LO;
	if ((signal_fail) || (phys > inst->limits.Lo + inst->limits.hys))
		inst->alarms &= ~SIGNAL_LO;
	
	if ((!signal_fail) && (phys <= inst->limits.LoLo))
		inst->alarms |= SIGNAL_LO_LO;
	if ((signal_fail) || (phys > inst->limits.LoLo + inst->limits.hys))
		inst->alarms &= ~SIGNAL_LO_LO;

	inst->value = phys;
}
