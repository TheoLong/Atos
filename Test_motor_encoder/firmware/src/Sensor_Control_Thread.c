#include "sensor_control_thread.h"


int df =2 ;
int ds = 2;
int FrontIR = 0;
int SideIR = 0;
int sendFront;
int sendSide;
int receive;
void SENSOR_CONTROL_THREAD_Initialize ( void )
{
    DRV_ADC_Open();
    //init 2 software timmer
    mytimer0 = xTimerCreate("Timer0", 125, pdTRUE, (void*)0, Callback1);
    mytimer1 = xTimerCreate("Timer1", 250, pdTRUE, (void*)0, Callback2);
    receive_q = xQueueCreate(8, sizeof(struct JsonResponse));
    BaseType_t ret = xTimerStart(mytimer0, (TickType_t)3);
    BaseType_t ret1 = xTimerStart(mytimer1,(TickType_t)3);
    if(ret == pdFAIL || mytimer0 == NULL || receive_q == NULL || ret1 == pdFAIL)
    {
        //sendToUART('c');
    }
}

void SENSOR_CONTROL_THREAD_Tasks ( void )
{
   
    struct JsonResponse js;
    BaseType_t ret = xQueueReceive(receive_q, &js, portMAX_DELAY);
    if(ret != pdTRUE)
    {
        //TODO: dbgHLT
    }
    if(js.tsk == 31)
    {
        receive = js.arg0;
        if(js.arg0 == sendFront && js.arg1 == sendSide)
        {
            struct JsonRequest jsr = {PIC_ID, 's', 0, 32, 0, 'p', 0, 0, 0};
            SendOverWiFi(jsr);

        }


    }
    else if(js.tsk == 49)
    {
        df = js.arg0;
        ds = js.arg1;
    }
   
}

void ReadIR(void)
{
    
    if (DRV_ADC_SamplesAvailable())
    {
        FrontIR = DRV_ADC_SamplesRead(0);
        SideIR = DRV_ADC_SamplesRead(1);
    }
    struct JsonResponse js = {49, 0, FrontIR, SideIR, 0, 0};
    SendToIRQueue(js);
}

void SendToIRQueue(struct JsonResponse js)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t ret = xQueueSendFromISR(receive_q, &js, &xHigherPriorityTaskWoken);
    if(ret==pdFALSE)
    {
        //sendToUART('f');
    }
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}


//----------------------------debug used-------------------------------------------------
void Callback1(TimerHandle_t xTimer)
{
    struct JsonRequest test = {PIC_ID,'s',0,31,0,FrontIR,SideIR,0,0};
    sendFront = FrontIR;
    sendSide  = SideIR;
    SendOverWiFi(test);
}

void Callback2(TimerHandle_t xTimer)
{
    struct JsonRequest jsr = {PIC_ID, 'r', PIC_ID, 31, 0, 0, 0, 0};
    SendOverWiFi(jsr);
}