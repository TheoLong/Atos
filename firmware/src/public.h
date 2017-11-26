#ifndef _PUBLIC_H    /* Guard against multiple inclusion */
#define _PUBLIC_H

#include <peripheral/usart/plib_usart.h>
#include <peripheral/ports/plib_ports.h>
#include <peripheral/adc/plib_adc.h>
#include <peripheral/int/plib_int.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "queue.h"
#include "timers.h"
#include "Accelerometer.h"

#define PIC_ID 4

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

void SendToServoQueue(struct JsonResponse js);





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
#endif /* _EXAMPLE_FILE_NAME_H */

