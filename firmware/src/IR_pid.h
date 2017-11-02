#ifndef _IR_PID_H
#define _IR_PID_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "public.h"
#include "queue.h"
// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END 

struct IR_Struct 
{
    int Front_IR;
    int Side_IR;
};
typedef struct IRC
{
    int FrontIR;
    int SideIR;
    int ircount;
    int distance;
} IRC;
typedef struct IRPID 
{
    float integral;
    int previous_error;
    float derivative;
    double Kp;
    double Ki;
    double Kd;
    int output;
    bool set_dir;
    bool enable;
    int cap;
    int set_distance;
    int set_speed;
} IRPID;
typedef struct IR_Struct IR;

void IR_PID_Initialize ( void );
void IR_PID_Tasks( void );
void ReadIR(void);
void SendToIRQueue(IR data);

#endif /* _IR_PID_H */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END
