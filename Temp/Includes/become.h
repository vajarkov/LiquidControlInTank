/* Automation Studio generated header file */
/* Do not edit ! */
/* become 1.00.0 */

#ifndef _BECOME_
#define _BECOME_
#ifdef __cplusplus
extern "C" 
{
#endif
#ifndef _become_VERSION
#define _become_VERSION 1.00.0
#endif

#include <bur/plctypes.h>

#ifndef _BUR_PUBLIC
#define _BUR_PUBLIC
#endif
/* Datatypes and datatypes of function blocks */
typedef enum anaAlarmsEnum
{	SIGNAL_NO_ALARM = 0,
	SIGNAL_OVER = 1,
	SIGNAL_UNDER = 2,
	SIGNAL_OPEN_LINE = 4,
	SIGNAL_HI_HI = 8,
	SIGNAL_HI = 16,
	SIGNAL_LO = 32,
	SIGNAL_LO_LO = 64
} anaAlarmsEnum;

typedef enum localRemoteSwitchEnum
{	SW_OFF = 0,
	SW_LOCAL = 1,
	SW_REMOTE = 2
} localRemoteSwitchEnum;

typedef struct Analog_Settings_type
{	float scale_h;
	float scale_l;
	float offset;
} Analog_Settings_type;

typedef struct Analog_Limits_typ
{	float HiHi;
	float Hi;
	float Lo;
	float LoLo;
	float hys;
} Analog_Limits_typ;

typedef struct Analog_FB
{
	/* VAR_INPUT (analog) */
	signed short raw;
	plcbyte ai_input_status;
	plcbyte ai_channel_num;
	signed short adc_up;
	signed short adc_dn;
	/* VAR_OUTPUT (analog) */
	float value;
	/* VAR (analog) */
	struct Analog_Settings_type sett;
	struct Analog_Limits_typ limits;
	enum anaAlarmsEnum alarms;
} Analog_FB_typ;



/* Prototyping of functions and function blocks */
_BUR_PUBLIC void Analog_FB(struct Analog_FB* inst);


#ifdef __cplusplus
};
#endif
#endif /* _BECOME_ */

