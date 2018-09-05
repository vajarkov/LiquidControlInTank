/* Automation Studio generated header file */
/* Do not edit ! */

#ifndef _BUR_1535185581_2_
#define _BUR_1535185581_2_

#include <bur/plctypes.h>

/* Constants */
#ifdef _REPLACE_CONST
#else
#endif


/* Variables */
_GLOBAL plcbit ack_alarms;
_GLOBAL plcbit block_pump_cmd;
_GLOBAL plcbit block_valve_cmd;
_GLOBAL plcbit block_manual;
_GLOBAL plcbit block_auto;
_GLOBAL plcbit mode_remote_manual;
_GLOBAL plcbit mode_remote_auto;
_GLOBAL plcbit cmd_valve_stop;
_GLOBAL plcbit cmd_valve_close;
_GLOBAL plcbit cmd_valve_open;
_GLOBAL plcbit cmd_pump_off;
_GLOBAL plcbit cmd_pump_on;
_GLOBAL struct Analog_Limits_typ level_limits;
_GLOBAL unsigned short timer_for_valve;
_GLOBAL plcbit general_alarm;
_GLOBAL plcbit alarm[20];
_GLOBAL unsigned char ai_input_status;
_GLOBAL struct Tank_typ TANK;
_GLOBAL struct Pump_typ PUMP;
_GLOBAL struct Valve_typ VALVE;





__asm__(".section \".plc\"");

/* Used IEC files */
__asm__(".ascii \"iecfile \\\"Logical/Global.var\\\" scope \\\"global\\\"\\n\"");

/* Exported library functions and function blocks */

__asm__(".previous");


#endif /* _BUR_1535185581_2_ */

