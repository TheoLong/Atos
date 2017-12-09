#include "control.h"
#include "statemachine.h"

QueueHandle_t receive_q;
TimerHandle_t controltimer;
bool started = false;


//struct StateMachineParams smp = {0, false, false, true, true, 0, MAXSTATE};
void CONTROL_Initialize ( void )
{
    PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, 6, 0);
    receive_q = xQueueCreate(128, sizeof(struct JsonResponse));
    controltimer = xTimerCreate("ControlTimer", 200, pdTRUE, (void*)0, requeststatus);
    BaseType_t ret = xTimerStart(controltimer, (TickType_t) 5);
    if(!receive_q)
    {
        //DBG: TODO;
    }
}

void CONTROL_Tasks ( void )
{
    vTaskDelay(250);
    struct JsonRequest jsr = {PIC_ID, 'r', PIC_ID, 63, 0, 0, 0, 0, 0};
    SendOverWiFi(jsr);
    static struct StateMachineParams smp = {0, false, false, true, true, 0, MAXSTATE};
    xTimerStart(controltimer, (TickType_t) 5);
    while(1)
    {        
        //smp.status = 1;
        struct JsonResponse js;
        BaseType_t ret = xQueueReceive(receive_q, &js, (TickType_t) 2);
        while (ret == pdTRUE)
        {
            if(js.tsk == 61 )
                smp.bumper = true;
            else if(js.tsk == 63)
            {
                if(js.arg0 < MAXSTATE && js.arg0 > INIT)
                {
                    smp.resumed = js.arg0;
                    smp.current_row = js.arg2;
                    smp.status = 1;
                    started = true;
                }
            }
            else if(js.tsk == 89)
            {
                if(!started && js.arg3 == 21)
                {
                    smp.status = 1;
                    started = true;
                }
                else if(started && js.arg3 == 99)
                    smp.status = 2;
                else if(started && js.arg3 == 50)
                {
                    smp.status = 5;
                }
            }
            ret = xQueueReceive(receive_q, &js, (TickType_t) 2);
        }
//        if(ret == pdTRUE)
//        {
//            if(js.tsk == 61 && js.arg0 == 1)
//                smp.bumper = true;
//            else if(js.tsk == 60)
//                smp.status = js.arg0;
//            else if(js.tsk == 79)
//            {
//                if(!started && js.arg3 == 21)
//                {
//                    smp.status = 1;
//                    started = true;
//                }
//                else if(started && js.arg3 == 99)
//                    smp.status = 2;
//                else if(started && js.arg3 == 50)
//                {
//                    smp.status = 5;
//                }
//            }
//        }
        if(started)
        {
            lori_state_machine(&smp);
        }
    }
}


void SendToControlQueue(struct JsonResponse js)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t ret = xQueueSendFromISR(receive_q, &js, &xHigherPriorityTaskWoken);
    if(ret==pdFALSE)
    {
        //sendToUART('f');
    }
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}