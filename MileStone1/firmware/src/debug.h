

#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "system_config.h"
#include "system_definitions.h"
#include "app_public.h"

#define TASK_ENTER 1
#define TASK_LOOP_ENTER 2
#define TASK_QUEUE_BEFORE_SEND 3
#define TASK_QUEUE_AFTER_SEND 4
#define TASK_QUEUE_BEFORE_RECEIVE 5
#define TASK_QUEUE_AFTER_RECEIVE 6

#define ISR_ENTER 7
#define ISR_EXIT 8
#define ISR_QUEUE_BEFORE_SEND 9
#define ISR_QUEUE_AFTER_SEND 10
#define ISR_QUEUE_BEFORE_RECEIVE 11
#define ISR_QUEUE_AFTER_RECEIVE 12



#define HALTED_QUEUE_CREATE 0xFA
#define HALTED_QUEUE_SEND 0xFB
#define HALTED_QUEUE_RECEIVE 0xFC

void dbgHalt(unsigned char reason);
void dbgOutputVal(unsigned char outVal);
void dbgUARTVal(unsigned char outVal);
void dbgOutputLoc(unsigned char outVal);

#endif
