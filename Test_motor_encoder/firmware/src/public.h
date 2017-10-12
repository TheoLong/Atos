#ifndef _PUBLIC_H    /* Guard against multiple inclusion */
#define _PUBLIC_H

#include <peripheral/usart/plib_usart.h>
#include <peripheral/ports/plib_ports.h>
#include <peripheral/adc/plib_adc.h>
#include <peripheral/int/plib_int.h>
#include <stdio.h>
#include "queue.h"
#include "timers.h"

#define PIC_ID 3

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
void SendToIRQueue(struct JsonResponse js);





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

//non-blocking
void Left_Motor_PID(bool dir, int speed);
void Right_Motor_PID(bool dir, int speed);
void SetServo1PWM(int pwm);
void SetServo2PWM(int pwm);
//blocking
void Left_Motor_Distance(bool dir, int speed, int distance);
void Right_Motor_Distance(bool dir, int speed, int distance);
void Move(int speed, int distance, bool dir);
void Left_Turn();
void Right_Turn();
//timming
//servo timming function
void Wait_Time(int time);

//encoder timming function
void Wait_Left();
void Wait_Right();
void Wait();

//wrapper, used only in special condition
bool Left_Is_Finish();
bool Right_Is_Finish();
void Timing_Wait(int time);
bool GetTimingFlag();



#endif /* _EXAMPLE_FILE_NAME_H */

