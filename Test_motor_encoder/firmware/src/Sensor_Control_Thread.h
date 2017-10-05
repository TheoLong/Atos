#ifndef _SENSOR_CONTROL_THREAD_H
#define _SENSOR_CONTROL_THREAD_H


#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "queue.h"
#include "timers.h"
#include "public.h"
// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
struct IR_Struct 
{
    int Front_IR;
    int Side_IR;
};
typedef struct IR_Struct IR;
void SENSOR_CONTROL_THREAD_Initialize ( void );
void SENSOR_CONTROL_THREAD_Tasks( void );
void ReadIR(void);

QueueHandle_t IR_Q;

TimerHandle_t mytimer0, mytimer1;
QueueHandle_t receive_q;
void Callback1(TimerHandle_t xTimer);
void Callback2(TimerHandle_t xTimer);

#endif /* _SENSOR_CONTROL_THREAD_H */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END


