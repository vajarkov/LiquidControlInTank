/* Automation Studio generated header file */
/* Do not edit ! */

#ifndef _BUR_1535185581_1_
#define _BUR_1535185581_1_

#include <bur/plctypes.h>

/* Datatypes and datatypes of function blocks */
typedef struct Pump_typ
{	plcbit status_running;
	plcbit status_remote;
	plcbit cmd_on;
	plcbit button_stop;
} Pump_typ;

typedef struct Valve_typ
{	plcbit status_remote;
	plcbit status_local;
	plcbit button_open;
	plcbit button_close;
	plcbit button_stop;
	plcbit signal_valve_opened;
	plcbit signal_valve_closed;
	plcbit cmd_valve_open;
	plcbit cmd_valve_close;
	struct Analog_FB feedback;
} Valve_typ;

typedef struct Tank_typ
{	struct Analog_FB level;
} Tank_typ;






__asm__(".section \".plc\"");

/* Used IEC files */
__asm__(".ascii \"iecfile \\\"Logical/Global.typ\\\" scope \\\"global\\\"\\n\"");

/* Exported library functions and function blocks */

__asm__(".previous");


#endif /* _BUR_1535185581_1_ */

