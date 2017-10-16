#include "app.h"
#include "timers.h"
#include "queue.h"

TimerHandle_t mytimer0;


void APP_Initialize ( void )
{
    mytimer0 = xTimerCreate("Timer0", 25, pdTRUE, (void*)0, Callback);
    xTimerStart(mytimer0, (TickType_t)3);
}


void APP_Tasks ( void )
{
    struct JsonRequest jsr = {PIC_ID, 's', 0, 12, 0, 0, 0, 0, 0};
    SendOverWiFi(jsr);
    while(true)
    {
        
    }
}

void Callback(TimerHandle_t xTimer)
{
//    struct JsonRequest jsr = {PIC_ID, 's', 0, 12, 0, 6666, 8888, 6666, 8888};
//    SendOverWiFi(jsr);
}

/*******************************************************************************
 End of File
 */
