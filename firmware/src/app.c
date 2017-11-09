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
    ServoTimer2 = xTimerCreate("ServoTimer2", 90, pdTRUE, (void*)1, ServoControlCallback2);
    ServoTimer3 = xTimerCreate("ServoTimer3", 500, pdTRUE, (void*)2, ServoControlCallback3);
    ServoQueue = xQueueCreate(128, sizeof(struct JsonResponse));
    if(ServoTimer1 == NULL || ServoQueue == NULL)
    {
        while(1)
        {
            
        }
    }    
//    DRV_OC0_PulseWidthSet(750);
}


void APP_Tasks ( void )
{
//    BaseType_t ret = xTimerStart(ServoTimer2, 5);
    BaseType_t ret = xTimerStart(ServoTimer1, 5); 
    BaseType_t ret2 = xTimerStart(ServoTimer3, 5);
    if(ret != pdPASS || ret2 != pdPASS)
    {
        ret = pdPASS;
    }
    struct JsonResponse jsr;
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
    static int pos = 525;
    static bool inc = true;
    if(inc && (pos >= 725))
        inc = false;
    else if(!inc && (pos <=525))
        inc = true;
    DRV_OC0_PulseWidthSet(pos);
    pos = (inc) ? (pos + 5) : (pos - 5);  
}

void ServoControlCallback2(TimerHandle_t xTimer)
{
    static int pos = 550;
    static int counter = 0;
    if(load)
    {
        load = false;
        counter = 0;
    }
    DRV_OC0_PulseWidthSet(pos);
    pos = (pos == 550) ? 700 : 550;
    if(counter >= 176)
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
