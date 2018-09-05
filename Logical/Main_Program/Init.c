
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{	
	VALVE.feedback.sett.scale_h = 100;
	VALVE.feedback.sett.scale_l = 0;
	timer_for_valve = 60;
	
	TANK.level.sett.scale_h = 0;
	TANK.level.sett.scale_l = 100;
	
	TANK.level.limits.HiHi = 95;
	TANK.level.limits.Hi = 90;
	TANK.level.limits.Lo = 10;
	TANK.level.limits.LoLo = 5;
	
	level_limits.Hi = 80;
	level_limits.Lo = 20;
	timer_for_pump = 3;
}
