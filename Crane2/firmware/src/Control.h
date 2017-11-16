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


void CONTROL_Initialize ( void );
void CONTROL_Tasks( void );
void requeststatus(TimerHandle_t xTimer);
#endif /* _CONTROL_H */


