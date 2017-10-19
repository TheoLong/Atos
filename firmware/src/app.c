#include "app.h"
#include "timers.h"
#include "queue.h"

TimerHandle_t mytimer0;
TimerHandle_t ServoTimer1, ServoTimer2, ServoTimer3;
QueueHandle_t ServoQueue;

bool load = false;

void APP_Initialize ( void )
{
    DRV_OC0_Start();
    DRV_TMR0_Start();
    ServoTimer1 = xTimerCreate("ServoTimer1", 10, pdTRUE, (void*)0, ServoControlCallback1);
    ServoTimer2 = xTimerCreate("ServoTimer2", 200, pdTRUE, (void*)1, ServoControlCallback2);
    ServoTimer3 = xTimerCreate("ServoTimer3", 500, pdTRUE, (void*)2, ServoControlCallback3);
    xTimerStart(ServoTimer1, (TickType_t)3);
    xTimerStart(ServoTimer3, (TickType_t)3);
    ServoQueue = xQueueCreate(128, sizeof(struct JsonResponse));
    if(ServoTimer1 == NULL || ServoQueue == NULL)
    {
        while(1)
        {
            
        }
    }    
//    mytimer0 = xTimerCreate("Timer0", 125, pdTRUE, (void*)0, Callback);
//    xTimerStart(mytimer0, (TickType_t)3);
}


void APP_Tasks ( void )
{
    BaseType_t ret = xTimerStart(ServoTimer1, 5);
    BaseType_t ret2 = xTimerStart(ServoTimer3, 5);
    if(ret != pdPASS || ret2 != pdPASS)
    {
        ret = pdPASS;
    }
    struct JsonResponse jsr;
    if(ret != pdPASS)
    {
        //
    }
    while(true)
    {
        BaseType_t ret = xQueueReceive(ServoQueue, &jsr, portMAX_DELAY);
        if(ret == pdTRUE)
        {
            if(jsr.tsk == 80 && jsr.arg0 == 1)
            {
                struct JsonRequest jsr = {3, 's', 3, 80, 0, 0, 0, 0, 0};
                SendOverWiFi(jsr);
                load = true;
                DRV_OC0_PulseWidthSet(800);
                vTaskDelay((TickType_t)140);
                xTimerStop(ServoTimer1, 5);
//                xTimerStop(ServoTimer3, 5);
                xTimerStart(ServoTimer2, 5);            
            }
        }

    }
}

void SendToServoQueue(struct JsonResponse js)
{
    BaseType_t ret = xQueueSendToBack(ServoQueue, (void*)&js, 5);
    if(ret != pdTRUE)
    {
        while(1)
        {
            
        }
    }
}

void ServoControlCallback1(TimerHandle_t xTimer)
{
    static int pos = 50;
    static bool inc = true;
    if(inc && (pos >= 850))
        inc = false;
    else if(!inc && (pos <=50))
        inc = true;
    DRV_OC0_PulseWidthSet(pos);
    pos = (inc) ? (pos + 6) : (pos - 6);  
}

void ServoControlCallback2(TimerHandle_t xTimer)
{
    static int pos = 50;
    static int counter = 0;
    if(load)
    {
        load = false;
        counter = 0;
    }
    DRV_OC0_PulseWidthSet(pos);
    pos = (pos == 50) ? 850 : 50;
    if(counter >= 75)
    {
        struct JsonRequest jsr = {3, 's', 0, 80, 0, 0, 0, 0, 0};
        SendOverWiFi(jsr);
        xTimerStop(xTimer, (TickType_t)10);
        xTimerStart(ServoTimer1, (TickType_t)5);
        counter = 0;
    }
    counter++;
}

void ServoControlCallback3(TimerHandle_t xTimer)
{
    struct JsonRequest js = {PIC_ID, 'r', 3, 80, 0, 0, 0, 0, 0};
    SendOverWiFi(js);    
}
/*******************************************************************************
 End of File
 */
