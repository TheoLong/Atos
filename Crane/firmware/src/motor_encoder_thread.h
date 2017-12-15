#ifndef _MOTOR_ENCODER_THREAD_H
#define _MOTOR_ENCODER_THREAD_H

// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "queue.h"
#include "timers.h"
#include <math.h>
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif

struct Timing_Struct 
{
    bool time;
};

typedef struct Timing_Struct timing;
void read_timing(void);
void SendToQueue(timing data);
QueueHandle_t Timing_Q;

typedef struct FLAG
{
    bool time_up;
    bool counter_start;
}FLAG;

typedef struct TIME_CONTROL
{
    int set_time;
    int counter;
}TIME_CONTROL;

typedef struct SERVO
{
    int pwm;
}SERVO;

#endif /* _MOTOR_ENCODER_THREAD_H */

#ifdef __cplusplus
}
#endif
