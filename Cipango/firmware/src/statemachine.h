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
    
    WAIT_FOR_START = 1,
    
    TRAVEL_TO_LORI = 2,
    ARRIVE_AT_LORI = 3,
    WAIT_FOR_LORI = 4,
            
    TRAVEL_TO_CRANE = 5,
    ARRIVE_AT_CRANE = 6,
    WAIT_FOR_CRANE = 7,
    
    STOP = 8
}Cipango_States;

struct StateMachineParams
{
    bool wait_for_start;
    
	bool lori_bumper;
    bool cipango_lori_ready;
    bool lori_done;
    
    bool crane_bumper;
    bool cipango_crane_ready;
	bool crane_done;
    
    char status;
};

void cipango_state(struct StateMachineParams * arg);

void _state_machine_wait_for_start(Cipango_States * state, Cipango_States * prev, struct StateMachineParams * arg);

void _state_machine_travel_to_lori(Cipango_States * state, Cipango_States * prev, struct StateMachineParams * arg);
void _state_machine_arrive_at_lori(Cipango_States * state, Cipango_States * prev, struct StateMachineParams * arg);
void _state_machine_wait_for_lori(Cipango_States * state, Cipango_States * prev, struct StateMachineParams * arg);

void _state_machine_travel_to_crane(Cipango_States * state, Cipango_States * prev, struct StateMachineParams * arg);
void _state_machine_arrive_at_crane(Cipango_States * state, Cipango_States * prev, struct StateMachineParams * arg);
void _state_machine_wait_for_crane(Cipango_States * state, Cipango_States * prev, struct StateMachineParams * arg);

void _state_machine_stop(Cipango_States * state, Cipango_States * prev, struct StateMachineParams * arg);

void _state_machine_send_status(Cipango_States * curr, Cipango_States * next);

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
