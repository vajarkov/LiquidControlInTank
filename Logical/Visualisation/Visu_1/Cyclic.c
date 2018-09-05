
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _CYCLIC ProgramCyclic(void)
{	
	if (VALVE.signal_valve_opened)
		valve_status = 1;
	else if (VALVE.signal_valve_closed)
		valve_status = 2;
	else if (!VALVE.signal_valve_closed && !VALVE.signal_valve_opened)
		valve_status = 3;
	else
		valve_status = 0;
	/*=========================*/
	if (PUMP.status_running)
		pump_status = 1;
	else
		pump_status = 0;
	/*=========================*/
	if (PUMP.status_remote)
		switch_mode_pump = 1;
	else
		switch_mode_pump = 0;
	/*=========================*/
	if (VALVE.status_local)
		switch_mode_valve = 0;
	else if (VALVE.status_remote)
		switch_mode_valve = 1;
	else
		switch_mode_valve = 2;
			
}
