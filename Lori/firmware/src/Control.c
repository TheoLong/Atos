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
}

void CONTROL_Tasks ( void )
{
//     Left_Motor_PID(FORWARD, 35);
//     Right_Motor_PID(FORWARD, 35);
    static struct StateMachineParams smp = {0, false, false, false, false, 0};
//    vTaskDelay((TickType_t) 1000);
    while(1)
    {
        smp.status = 1;
        struct JsonResponse js;
        BaseType_t ret = xQueueReceive(receive_q, &js, (TickType_t) 2);
        if(ret == pdTRUE)
        {
            if(js.tsk == 61 && js.arg0 == 1)
                smp.bumper = true;
            else 
            {
                if(js.tsk == 79 && js.arg0 == 1)
                {
                    smp.loriready = true;
                }
                if(js.tsk == 79 && js.arg1 == 1 && js.arg3 == 4)
                {
                    smp.cipangoready = true;
                }
                if(js.tsk == 79 && js.arg0 == 0 && js.arg1 == 0)
                {
                    smp.postdump = true;
                }
            }
                
        }
        lori_state_machine(&smp);
    }
}


void ReadIR(void)
{
    int FrontIR = 0;
    int SideIR = 0;
    if (DRV_ADC_SamplesAvailable())
    {
        FrontIR =  DRV_ADC_SamplesRead(0);
        SideIR = DRV_ADC_SamplesRead(1);
        struct JsonResponse js = {49, 0, FrontIR, SideIR, 0, 0};
        SendToControlQueue(js);        
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
