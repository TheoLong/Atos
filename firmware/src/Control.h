#ifndef _CONTROL_H
#define _CONTROL_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "public.h"
#include "timers.h"

extern bool bumper;

typedef enum
{
	CONTROL_STATE_INIT=0,
    CONTROL_STATE_RUN_TESTS,
	CONTROL_STATE_SERVICE_TASKS,
    CONTROL_STATE_STANDBY,
    CONTROL_STATE_SWEEP,
    CONTROL_STATE_APPROACH,
            CONTROL_STATE_BACK,
    CONTROL_STATE_DUMP,
            CONTROL_STATE_TURN_RIGHT,
            CONTROL_STATE_TURN_LEFT,
            CONTROL_STATE_TARE,
            CONTROL_STATE_PREDUMP,
    CONTROL_STATE_END,
} CONTROL_STATES;


typedef struct
{
    CONTROL_STATES state;
    int current_row;
    bool enterstandby;
    bool standby;
    bool enterturnleft;
    bool entertare;
    bool entersweep;
    bool enterback;
    bool enterturnright;
    bool dump;
} CONTROL_DATA;

void CONTROL_Initialize ( void );
void CONTROL_Tasks( void );
void ReadIR(void);
void LoriTimer1CallBack(TimerHandle_t xTimer);

#endif /* _CONTROL_H */


