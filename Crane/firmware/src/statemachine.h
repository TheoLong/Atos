#ifndef _STATEMACHINE_H    /* Guard against multiple inclusion */
#define _STATEMACHINE_H

#include "public.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef enum
{
	INIT = 0,
	STANDBY,
	SWEEP,
	BACK,
	TURN_RIGHT,
	TURN_LEFT,
	TARE,
	PREDUMP,
	DUMP,
    PAUSED,
    END,
	MAXSTATE
}Lori_States;

struct StateMachineParams
{
	unsigned char current_row;
	bool standby;
	bool bumper;
	bool dump;
	bool cipangoready;
    char status;
};

void lori_state_machine(struct StateMachineParams * arg);
void _state_machine_standby(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg);
void _state_machine_turnright(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg);
void _state_machine_tare(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg);
void _state_machine_sweep(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg);
void _state_machine_back(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg);
void _state_machine_turnleft(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg);
void _state_machine_predump(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg);
void _state_machine_dump(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg);

void _state_machine_send_status(Lori_States * curr, Lori_States * next);

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
