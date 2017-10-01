#include "app.h"
#include "timers.h"
#include "queue.h"

TimerHandle_t mytimer0;


void APP_Initialize ( void )
{
    mytimer0 = xTimerCreate("Timer0", 125, pdTRUE, (void*)0, Callback);
    xTimerStart(mytimer0, (TickType_t)3);
}


void APP_Tasks ( void )
{
    while(true)
    {
        
    }
}

void Callback(TimerHandle_t xTimer)
{
//    char str[256];
//    struct JsonRequest js;
//    struct MessageStat msg = GetMessageStat();
//    js.seq = 0;
//    js.id = PIC_ID;
//    js.tgt = 0;
//    js.tp = 's';
//    js.tsk = 11;
//    js.arg0 = msg.total;
//    js.arg1 = msg.good;
//    js.arg2 = msg.corrupted;
//    js.arg3 = msg.missed;
//    if(msg.corrupted + msg.missed > 128)
//    {
//        //TODO: dbgHLT
//    }
//    JsonToString(js, str);
//    SendToTransmitQueue(str);
    // struct JsonRequest jsr = {PIC_ID, 'r', 15, 15, 15, 15, 15, 15, 15};
    // SendOverWiFi(jsr);
}

/*******************************************************************************
 End of File
 */
