#ifndef _PUBLIC_H    /* Guard against multiple inclusion */
#define _PUBLIC_H

#include <peripheral/usart/plib_usart.h>
#include <peripheral/ports/plib_ports.h>
#include <peripheral/adc/plib_adc.h>
#include <peripheral/int/plib_int.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "timers.h"
#include "queue.h"
#define PIC_ID 3
#define FORWARD false
#define BACKWARD true
struct JsonResponse
{
    uint8_t tsk;
    uint16_t seq;
    int arg0;
    int arg1;
    int arg2;
    int arg3;
};

struct JsonRequest
{
    uint8_t id;
    uint8_t tp;
    uint8_t tgt;
    uint8_t tsk;
    uint16_t seq;
    int arg0;
    int arg1;
    int arg2;
    int arg3;    
};

//returns xHigherPriorityTaskWaken
//should use this value in portEND_SWITCHING_ISR()
BaseType_t SendOverWiFi(struct JsonRequest js);

//when connection is good, return 1, otherwise 0
uint8_t GetConnectionStatus();
//YunfeiGuo's IRQueue
void SendToControlQueue(struct JsonResponse js);

struct MessageStat
{
    short total;
    short corrupted;
    short missed;
    short good;
    short sequence;
};
uint32_t hash(unsigned char * str);
struct MessageStat GetMessageStat();

//servo control
void SetServoRotorPWM(int pwm);
void SetServoGripperPWM(int pwm);
void SetServoWinchPWM(int pwm);
void SetServoWristPWM(int pwm);
//-----------------------------------------
void Timing_Wait(int time);
bool GetTimingFlag();
//servo timming function
void Wait_Time(int time);

extern bool bumperA;
extern bool bumperB;
void SendToControlQueue(struct JsonResponse js);

#endif /* _EXAMPLE_FILE_NAME_H */
