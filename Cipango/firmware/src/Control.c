#include "control.h"
#include "statemachine.h"

QueueHandle_t receive_q;
TimerHandle_t controltimer;

void CONTROL_Initialize ( void )
{
    receive_q = xQueueCreate(128, sizeof(struct JsonResponse));
    controltimer = xTimerCreate("ControlTimer", 200, pdTRUE, (void*)0, requeststatus);
    DRV_ADC_Open();
    DRV_ADC_Start();
    BaseType_t ret = xTimerStart(controltimer, (TickType_t) 5);
    if(!receive_q)
    {
        //DBG: TODO;
    }
    Pause();
}

void CONTROL_Tasks ( void )
{
//    Left_Motor_PID(FORWARD, 5);
//    Right_Motor_PID(FORWARD, 25);
    static struct StateMachineParams smp = {false, false, false, false, false, false, false, 0};
    //vTaskDelay((TickType_t) 1000);
    while(1)
    {
        struct JsonResponse js;
        BaseType_t ret = xQueueReceive(receive_q, &js, (TickType_t) 2);
        if(ret == pdTRUE)
        {
            int temp = 0;
            
            if (js.tsk == 71 && js.arg0 == 1)
            {                
                smp.lori_bumper = true;
            }
            if (js.tsk == 72 && js.arg0 == 1)
            {
                smp.crane_bumper = true;
            }
            if (js.tsk == 79 && js.arg1 == 1 && js.arg2 == 0 && js.arg3 == 3)
            {                
                smp.cipango_lori_ready = true;
            }
            if (js.tsk == 79 && js.arg0 == 0 && js.arg1 == 0 && js.arg3 == 4)
            {                
                smp.lori_done = true;
            }
            if (js.tsk == 79 && js.arg1 == 0 && js.arg2 == 1 && js.arg3 == 6)
            {                
                smp.cipango_crane_ready = true;
            }
            if (js.tsk == 79 && js.arg2 == 0 && js.arg3 == 7)
            {     
                smp.crane_done = true;
            }
            if(js.tsk == 79 && js.arg3 > 20)
            {
//                smp.lori_bumper = false;
//                smp.cipango_lori_ready = false;
//                smp.lori_done = false;    
//                smp.crane_bumper = false;
//                smp.cipango_crane_ready = false;
//                smp.crane_done = false;    
//                smp.status = 0;
                
                if (js.arg1 == 1)
                {
                    smp.cipango_lori_ready = true;
                }
                smp.status = js.arg3;
            }
            
            struct JsonRequest js_left = {PIC_ID, 's',0, 45, 0, temp, 0, 0, 0};
            //SendOverWiFi(js_left);
        }
        cipango_state(&smp);
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
