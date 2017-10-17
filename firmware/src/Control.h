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

typedef enum
{
	CONTROL_STATE_INIT=0,
    CONTROL_STATE_RUN_TESTS,
	CONTROL_STATE_SERVICE_TASKS,
    CONTROL_STATE_END,
} CONTROL_STATES;


typedef struct
{
    CONTROL_STATES state;
} CONTROL_DATA;

void CONTROL_Initialize ( void );
void CONTROL_Tasks( void );
void ReadIR(void);

#endif /* _CONTROL_H */


