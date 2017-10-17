#include "app.h"
#include "timers.h"
#include "queue.h"

TimerHandle_t mytimer0;

void APP_Initialize ( void )
{
    DRV_OC0_Start();
    mytimer0 = xTimerCreate("Timer0", 125, pdTRUE, (void*)0, Callback);
    xTimerStart(mytimer0, (TickType_t)3);
}


void APP_Tasks ( void )
{

}

void Callback(TimerHandle_t xTimer)
{

}

/*******************************************************************************
 End of File
 */
